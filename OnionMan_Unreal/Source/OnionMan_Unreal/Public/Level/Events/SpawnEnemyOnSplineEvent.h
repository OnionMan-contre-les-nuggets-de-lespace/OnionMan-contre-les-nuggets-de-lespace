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
private:
	AEnemyOnSplineActor* m_enemyPrefab;
    USplineComponent* m_spline;

public:
	USpawnEnemyOnSplineEvent(/* args */);

protected:
	virtual AEnemyActor* SpawnEnemy() override;
	
};
