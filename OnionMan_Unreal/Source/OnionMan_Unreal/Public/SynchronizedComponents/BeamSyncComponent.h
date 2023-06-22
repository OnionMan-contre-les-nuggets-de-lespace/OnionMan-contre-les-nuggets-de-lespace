// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "../Network/SpecializedProperties/bool/Synchronizedbool.h"
#include "BeamSyncComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Network), meta=(BlueprintSpawnableComponent) )
class ONIONMAN_UNREAL_API UBeamSyncComponent : public USynchronizedActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedBool* BeamPhaseReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedBool* BeamIsReady;

	virtual void LoadProperties() override;
};
