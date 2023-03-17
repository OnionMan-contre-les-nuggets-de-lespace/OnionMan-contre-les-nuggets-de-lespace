// Fill out your copyright notice in the Description page of Project Settings.


#include "OnionManGameInstance.h"

void UOnionManGameInstance::Init()
{
    UGameInstance::Init();
    NetworkManager = NewObject<UNetworkManager>();
}
