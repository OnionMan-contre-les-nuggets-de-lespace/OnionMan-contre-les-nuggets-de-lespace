// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/SynchronizedActorComponent.h"
#include "Network/SynchronizedProperty.h"
#include "Network/SynchronizedFStringProperty.h"
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
	//USynchronizedProperty<int> SP0{9, 12};
	//USynchronizedProperty<FString> SP1{ "Waw", 32 };
	//USynchronizedFStringProperty SP2{ "Waw", 2 };

	void LoadProperties() override;

	//UFUNCTION(BlueprintCallable)
	/*USynchronizedFStringProperty* GetSP2()
	{
		return &SP2;
	}*/


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
