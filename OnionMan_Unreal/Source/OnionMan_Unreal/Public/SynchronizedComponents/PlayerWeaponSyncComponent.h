// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "Network/SpecializedProperties/int/Synchronizedint.h"
#include "PlayerWeaponSyncComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Network), meta=(BlueprintSpawnableComponent) )
class ONIONMAN_UNREAL_API UPlayerWeaponSyncComponent : public USynchronizedActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Network", meta = (ShowInnerProperties))
	USynchronizedInt* CurrentWeapon;

public:
	virtual void LoadProperties() override;
	
};
