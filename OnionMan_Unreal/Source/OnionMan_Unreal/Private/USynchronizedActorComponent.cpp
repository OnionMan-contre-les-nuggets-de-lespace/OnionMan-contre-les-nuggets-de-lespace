// Fill out your copyright notice in the Description page of Project Settings.


#include "USynchronizedActorComponent.h"
#include "ISynchronizedPropertyBase.h"
#include "EncodingUtility.h"

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
	Super::BeginPlay();

	LoadProperties();
	// ...
	
}


// Called every frame
void USynchronizedActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


const uint32 USynchronizedActorComponent::ObjectID() const
{
	return m_objectID;
}

const TMap<uint16, ISynchronizedPropertyBase&> USynchronizedActorComponent::Properties() const
{
	return m_synchronizedProperties;
}

ObjectNeedSyncResult USynchronizedActorComponent::NeedSync()
{
	m_encodedPropertiesSize = 0;
	for (ISynchronizedPropertyBase& property : GetPropertiesToSync())
	{
		m_encodedPropertiesSize += property.GetEncodedPropertySize();
	}
	return ObjectNeedSyncResult(enabled && m_encodedPropertiesSize > 0, sizeof(int) + sizeof(uint32) + m_encodedPropertiesSize); // Size + ID + EncodedProperties
}

void USynchronizedActorComponent::PutEncodedObjectToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true)
{
	EncodingUtility::PutEncodedValueInBuffer<int>(m_encodedPropertiesSize + sizeof(uint32), buffer, offset); // Put Size
	EncodingUtility::PutEncodedValueInBuffer<uint32>(m_objectID, buffer, offset);                            // Put ID

	for (ISynchronizedObjectBase& property : GetPropertiesToSync())
	{
		property.PutEncodedPoropertyToBuffer(buffer, offset, forSync);                                       // Put all Properties
	}
}

TArray<uint8>& USynchronizedActorComponent::EncodeObject(bool forSync = true)
{
	TArray<uint8> encodedObject{}
	encodedObject.Reserve(m_encodedPropertiesSize + sizeof(int) + sizeof(uint32)); = EncodingUtility.Encode(m_objectID);

	encodedObject.Append(EncodingUtility::Encode<int>(m_encodedPropertiesSize + sizeof(uint32))); // Put Size
	encodedObject.Append(EncodingUtility::Encode<uint32>(m_objectID)); 							  // Put ID

	for (ISynchronizedObjectBase& property : GetPropertiesToSync())
	{
		encodedObject.Append(property.EncodeProperty(forSync));									  // Put all Properties
	}

	return encodedObject;
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

		if (m_synchronizedProperties.TryGetValue(propertyID, out ISynchronizedProperty synchronizedProperty))
		{
			synchronizedProperty.DecodeProperty(encodedProperties, offset, dataSize);
			if (offset - porpertyStartOffset != propertySize)
			{
				// Debug.LogError("Offset Overflow !");
			}
		}
		else
		{
			throw "There are no object with ID " << propertyID;
		}
	}
}

TArray<ISynchronizedPropertyBase&> USynchronizedActorComponent::GetPropertiesToSync()
{
	TArray<ISynchronizedPropertyBase&> propertiesToSync{};
	for (ISynchronizedPropertyBase& prop : m_synchronizedProperties.Values)
	{
		if (prop.NeedSync())
		{
			propertiesToSync.Add(prop);
		}
	}
	return propertiesToSync;
}

void USynchronizedActorComponent::AddSynchronizedProperty(ISynchronizedObjectBase& synchronizedProperty)
{
	synchronizedProperty.Init();

	uint16 propID = synchronizedProperty.PropertyID();
	if (m_synchronizedProperties.Contains(propID))
	{
		throw "The ID " << propID << " is already used by " << m_synchronizedProperties[propID];
	}
	m_synchronizedProperties.Add(propID, synchronizedProperty);
}