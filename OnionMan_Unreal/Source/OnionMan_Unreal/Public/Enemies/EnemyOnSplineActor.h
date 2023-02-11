// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyActor.h"
#include "Components/SplineComponent.h"
#include "EnemyOnSplineActor.generated.h"

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API AEnemyOnSplineActor : public AEnemyActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	USplineComponent* m_trajectory;

public:
	void Spawn(USplineComponent* trajectory);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void Move(float deltaTime, float timeSinceSpawn) override;


	// Editor
	virtual void EditorLoad(float timeSinceSpawn) override;
	virtual void EditorUpdate(float newTimeSinceSpawn) override;
	virtual void EditorUnload() override;
	
};
