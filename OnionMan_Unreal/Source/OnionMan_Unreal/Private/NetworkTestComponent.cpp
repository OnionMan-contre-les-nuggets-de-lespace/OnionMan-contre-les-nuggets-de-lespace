// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkTestComponent.h"
#include "NetworkManager.h"
#include "EncodingUtility.h"
#include "LogUtils.h"

using namespace OnionMan::Network;

void UNetworkTestComponent::LoadProperties()
{
	AddSynchronizedProperty(&SP0);
	AddSynchronizedProperty(&SP1);
	//AddSynchronizedProperty(&SP2);
}


// Called every frame
void UNetworkTestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_firstFrame) 
	{
		m_firstFrame = false;

		TArray<uint8> encodedObjects;
		NetworkManager::Instance().EncodeObjects(encodedObjects);

		FString encodedString = EncodingUtility::GetBytesAsString(encodedObjects);

		LOG_ERROR("Encoded string : %s", *encodedString);
	}
}
