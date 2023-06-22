// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "../Network/SpecializedProperties/bool/Synchronizedbool.h"
#include "../Network/SpecializedProperties/FIntVector/SynchronizedFIntVector.h"
#include "ShipParticlesSyncComponent.generated.h"


UCLASS( ClassGroup=(Network), meta=(BlueprintSpawnableComponent) )
class ONIONMAN_UNREAL_API UShipParticlesSyncComponent : public USynchronizedActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedBool* IsRoomScanned;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedFIntVector* RightComputerResultAnswer;

public:	
	// Sets default values for this component's properties
	UShipParticlesSyncComponent();

	virtual void LoadProperties() override;
};
