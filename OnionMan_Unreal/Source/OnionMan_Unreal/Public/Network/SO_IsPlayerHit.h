// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "SpecializedProperties/bool/Synchronizedbool.h"
#include "SO_IsPlayerHit.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class ONIONMAN_UNREAL_API USO_IsPlayerHit : public USynchronizedActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedBool* isPlayerHit;

	virtual void LoadProperties() override;
};

