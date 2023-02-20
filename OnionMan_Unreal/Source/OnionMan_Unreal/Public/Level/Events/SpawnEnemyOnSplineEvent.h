// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Events/SpawnEnemyEvent.h"
#include "../../Enemies/EnemyOnSplineActor.h"
#include "Components/SplineComponent.h"
#include "SpawnEnemyOnSplineEvent.generated.h"

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API USpawnEnemyOnSplineEvent : public USpawnEnemyEvent
{
	GENERATED_BODY()
protected:
	AEnemyOnSplineActor* m_enemyPrefab;
    USplineComponent* m_spline;
	TArray<AEnemyOnSplineActor*> m_editorEnemies;


public:
	USpawnEnemyOnSplineEvent(/* args */);

    // Editor
    virtual void EditorLoad(float timeSinceStart) override;
    virtual void EditorUpdate(float newTimeSinceStart) override;
    virtual void EditorUnload() override;

    virtual void EditorSave() override;

protected:
	virtual AEnemyActor* SpawnEnemy() override;
	
};
