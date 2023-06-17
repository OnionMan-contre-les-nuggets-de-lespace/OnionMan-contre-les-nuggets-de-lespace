// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Events/SpawnEnemyEvent.h"
#include "../../Enemies/IndependantEnemyActor.h"
#include "SpawnEnemyAtPositionEvent.generated.h"

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API USpawnEnemyAtPositionEvent : public USpawnEnemyEvent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Enemy Prefab")
	AIndependantEnemyActor* m_enemyPrefab;
	UPROPERTY(EditAnywhere, DisplayName = "Start Position")
	FVector m_startPosition;


	TArray<AIndependantEnemyActor*> m_editorEnemies;

public:
	USpawnEnemyAtPositionEvent(/* args */);

	// Editor
	virtual void EditorLoad(float timeSinceStart, AActor* levelAsset) override;
	virtual void EditorUpdate(float newTimeSinceStart) override;
	virtual void EditorUnload() override;

	virtual void EditorSave() override;

protected:
	virtual TObjectPtr<AEnemyActor> SpawnEnemy() override;
};