// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "../Network/SpecializedProperties/int/Synchronizedint.h"
#include "GameStateSyncComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Network), meta=(BlueprintSpawnableComponent) )
class ONIONMAN_UNREAL_API UGameStateSyncComponent : public USynchronizedActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedInt* GameState;

public:
	virtual void LoadProperties() override;
	
};
