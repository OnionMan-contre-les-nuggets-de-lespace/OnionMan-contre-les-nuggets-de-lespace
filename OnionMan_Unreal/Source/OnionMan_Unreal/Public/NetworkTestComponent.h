// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USynchronizedActorComponent.h"
#include "USynchronizedProperty.h"
#include "NetworkTestComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class ONIONMAN_UNREAL_API UNetworkTestComponent : public USynchronizedActorComponent
{
	GENERATED_BODY()

private:
	bool m_firstFrame = true;
	

public:
	USynchronizedProperty<int> SP0{9, 12};
	USynchronizedProperty<FString> SP1{"Waw", 32};

	void LoadProperties() override;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
