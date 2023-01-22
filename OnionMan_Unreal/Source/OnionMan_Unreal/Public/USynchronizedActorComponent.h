// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedObjectBase.h"
#include "Components/ActorComponent.h"
#include "USynchronizedActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONIONMAN_UNREAL_API UUSynchronizedActorComponent : public UActorComponent, public ISynchronizedObjectBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUSynchronizedActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
