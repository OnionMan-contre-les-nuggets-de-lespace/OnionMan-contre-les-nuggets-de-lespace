// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyActor.h"
#include "IndependantEnemyActor.generated.h"

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API AIndependantEnemyActor : public AEnemyActor
{
	GENERATED_BODY()

public:
	void Spawn(FVector startPosition);

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void Move(float deltaTime, float timeSinceSpawn) override;


	// Editor
#if WITH_EDITOR
	virtual void EditorLoad(float timeSinceSpawn) override;
	virtual void EditorLoadAtPosition(float timeSinceSpawn, FVector startPosition);
	virtual void EditorUpdate(float newTimeSinceSpawn) override;
	virtual void EditorUpdateAtPosition(float newTimeSinceSpawn, FVector startPosition);
	virtual void EditorUnload() override;
#endif
	
};
