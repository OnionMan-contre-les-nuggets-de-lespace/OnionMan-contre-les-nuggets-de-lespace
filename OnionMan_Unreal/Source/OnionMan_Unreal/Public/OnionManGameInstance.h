// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Network/NetworkManager.h"
#include "OnionManGameInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ONIONMAN_UNREAL_API UOnionManGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    UNetworkManager* NetworkManager;

    virtual void Init() override;
};
