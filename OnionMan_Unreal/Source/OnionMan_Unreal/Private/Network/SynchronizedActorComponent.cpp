// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SynchronizedActorComponent.h"
#include "Network/ISynchronizedPropertyBase.h"
#include "Network/EncodingUtility.h"
#include "Network/NetworkManager.h"

#include "LogUtils.h"

using namespace OnionMan::Network;

// Sets default values for this component's properties
USynchronizedActorComponent::USynchronizedActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USynchronizedActorComponent::BeginPlay()
{
	UActorComponent::BeginPlay();

	LoadProperties();
	UNetworkManager::Instance().AddSynchronizedObject(*this);
	// ...
	
}

void USynchronizedActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UNetworkManager::Instance().EndPlay();
}


// Called every frame
void USynchronizedActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


const uint32 USynchronizedActorComponent::ObjectID() const
{
	return m_objectID;
}

const TMap<uint16, TObjectPtr<ISynchronizedPropertyBase>>& USynchronizedActorComponent::Properties() const
{
	return m_synchronizedProperties;
}

ObjectNeedSyncResult USynchronizedActorComponent::NeedSync()
{
	m_encodedPropertiesSize = 0;

	TArray<TObjectPtr<ISynchronizedPropertyBase>> propertiesToSync{};
	GetPropertiesToSync(propertiesToSync);
	for (TObjectPtr<ISynchronizedPropertyBase> property : propertiesToSync)
	{
		m_encodedPropertiesSize += property->GetEncodedPropertySize();
	}
	return ObjectNeedSyncResult(/*enabled &&*/ m_encodedPropertiesSize > 0, sizeof(int) + sizeof(uint32) + m_encodedPropertiesSize); // Size + ID + EncodedProperties
}

void USynchronizedActorComponent::PutEncodedObjectToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
	EncodingUtility::PutEncodedValueInBuffer<int>(m_encodedPropertiesSize + sizeof(uint32), buffer, offset); // Put Size
	EncodingUtility::PutEncodedValueInBuffer<uint32>(m_objectID, buffer, offset);                            // Put ID

	TArray<TObjectPtr<ISynchronizedPropertyBase>> propertiesToSync{};
	GetPropertiesToSync(propertiesToSync);
	for (TObjectPtr<ISynchronizedPropertyBase> property : propertiesToSync)
	{
		property->PutEncodedPropertyToBuffer(buffer, offset, forSync);                                       // Put all Properties
	}
}

void USynchronizedActorComponent::DecodeObject(TArray<uint8>& encodedProperties, int& offset, int size)
{
	int objectStartOffset = offset;
	while (offset < size + objectStartOffset)
	{
		int propertySize = EncodingUtility::Decode<int>(encodedProperties, offset);
		int porpertyStartOffset = offset;

		uint16 propertyID = EncodingUtility::Decode<uint16>(encodedProperties, offset);
		int dataSize = propertySize - sizeof(uint16);

		if (m_synchronizedProperties.Contains(propertyID))
		{
			TObjectPtr<ISynchronizedPropertyBase> synchronizedProperty = m_synchronizedProperties[propertyID];
			synchronizedProperty->DecodeProperty(encodedProperties, offset, dataSize);
			if (offset - porpertyStartOffset != propertySize)
			{
				LOG_ERROR("Offset Overflow !");
			}
		}
		else
		{
			LOG_ERROR("There are no object with ID %i", propertyID)
		}
	}
}

void USynchronizedActorComponent::LoadProperties()
{
}


void USynchronizedActorComponent::GetPropertiesToSync(TArray<TObjectPtr<ISynchronizedPropertyBase>>& result)
{
	for (TObjectPtr<ISynchronizedPropertyBase> prop : m_propertiesArray)
	{
		if (prop->NeedSync())
		{
			result.Add(prop);
		}
	}
}

void USynchronizedActorComponent::AddSynchronizedProperty(TObjectPtr<ISynchronizedPropertyBase> synchronizedProperty)
{
	synchronizedProperty->Init();

	uint16 propID = synchronizedProperty->PropertyID();
	if (m_synchronizedProperties.Contains(propID))
	{
		LOG_ERROR("The ID %i is already used", propID);
	}
	else 
	{
		m_synchronizedProperties.Add(propID, synchronizedProperty);
		m_propertiesArray.Add(synchronizedProperty);
	}
}