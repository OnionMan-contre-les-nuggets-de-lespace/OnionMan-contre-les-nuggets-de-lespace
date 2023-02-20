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
	AIndependantEnemyActor* m_enemyPrefab;
    FVector3f m_startPosition;
	TArray<AIndependantEnemyActor*> m_editorEnemies;


public:
	USpawnEnemyAtPositionEvent(/* args */);

    // Editor
    virtual void EditorLoad(float timeSinceStart) override;
    virtual void EditorUpdate(float newTimeSinceStart) override;
    virtual void EditorUnload() override;

    virtual void EditorSave() override;

protected:
	virtual AEnemyActor* SpawnEnemy() override;
	
}
