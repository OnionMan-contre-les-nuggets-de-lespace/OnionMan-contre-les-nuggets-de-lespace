// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "../Network/SpecializedProperties/bool/Synchronizedbool.h"
#include "PlayerHitSyncComponent.generated.h"


UCLASS( ClassGroup=(Network), meta=(BlueprintSpawnableComponent) )
class ONIONMAN_UNREAL_API UPlayerHitSyncComponent : public USynchronizedActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedBool* IsPlayerHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedBool* HasRepairedCriticalRoom;

public:	
	// Sets default values for this component's properties
	UPlayerHitSyncComponent();

	virtual void LoadProperties() override;

		
};
