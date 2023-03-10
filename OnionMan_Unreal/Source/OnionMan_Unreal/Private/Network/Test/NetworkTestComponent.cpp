// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Test/NetworkTestComponent.h"
#include "Network/NetworkManager.h"
#include "Network/EncodingUtility.h"
#include "LogUtils.h"

using namespace OnionMan::Network;

void UNetworkTestComponent::LoadProperties()
{
	AddSynchronizedProperty(SP0);
	AddSynchronizedProperty(SP1);
	AddSynchronizedProperty(SP2);
	AddSynchronizedProperty(SP3);
	//AddSynchronizedProperty(&SP0);
	//AddSynchronizedProperty(&SP1);
	//AddSynchronizedProperty(&SP2);
}


// Called every frame
void UNetworkTestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	USynchronizedActorComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_firstFrame) 
	{
		m_firstFrame = false;

	}
}

void UNetworkTestComponent::EncodeAll()
{
	TArray<uint8> encodedObjects;
	UNetworkManager::Instance().EncodeObjects(encodedObjects);

	FString encodedString = EncodingUtility::GetBytesAsString(encodedObjects);

	LOG_ERROR("Encoded string : %s", *encodedString);
}

void UNetworkTestComponent::DecodeAll()
{
	TArray<uint8> encodedBytes{};
	EncodingUtility::GetStringAsBytes(EncodedString, encodedBytes);

	UNetworkManager::Instance().DecodeObjects(encodedBytes);
}
