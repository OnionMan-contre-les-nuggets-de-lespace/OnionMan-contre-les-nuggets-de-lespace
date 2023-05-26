// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/Test/NetworkTestComponent.h"

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

void UNetworkTestComponent::BeginPlay()
{
    USynchronizedActorComponent::BeginPlay();

    UOnionManGameInstance* gameInstance = Cast<UOnionManGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    if (gameInstance == nullptr)
    {
        LOG_ERROR("Incorrect GameInsance (Require UOnionManGameInstance)");
    }
    else
    {
        m_networkManager = gameInstance->NetworkManager;
    }
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
    TArray<uint8> encodedObjects{};
    m_networkManager->EncodeObjects(encodedObjects);

    FString encodedString = EncodingUtility::GetBytesAsString(encodedObjects);

    LOG_ERROR("Encoded string : %s", *encodedString);
}

void UNetworkTestComponent::DecodeAll()
{
    TArray<uint8> encodedBytes{};
    EncodingUtility::GetStringAsBytes(EncodedString, encodedBytes);

    m_networkManager->DecodeObjects(encodedBytes);
}
