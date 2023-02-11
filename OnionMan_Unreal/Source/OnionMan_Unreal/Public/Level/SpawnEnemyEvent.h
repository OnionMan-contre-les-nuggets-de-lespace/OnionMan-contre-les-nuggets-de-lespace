// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseWaveEvent.h"
#include "Enemies/EnemyActor.h"

#include "SpawnEnemyEvent.generated.h"

struct SpawnedEnnemy
{
private:
    AEnemyActor* m_enemyObject;
    float m_spawnTime;

public:
    SpawnedEnnemy(AEnemyActor* enemy, float spawnTime)
    {
        m_enemyObject = enemy;
        m_spawnTime = spawnTime;
    }

    AEnemyActor* Enemy() const
    {
        return m_enemyObject;
    }

    float SpawnTime() const
    {
        return m_spawnTime;
    }
};

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API USpawnEnemyEvent : public UBaseWaveEvent
{
	GENERATED_BODY()

private:
    AEnemyActor* m_enemyPrefab;

    int m_numberOfEnemiesToSpawn = 1;
    float m_timeBetweenSpawns = 0.0f;

    //Cache 
    TArray<SpawnedEnnemy> m_spawnedEnemies;

public:
    USpawnEnemyEvent(/* args */);

    virtual void Load() override;
    virtual void Start() override;
    virtual void Update(float deltaTime, float currentWaveTime) override;
    virtual void OnWaveEnd() override;

    // Editor
    virtual void EditorLoad(float time) override;
    virtual void EditorUnload() override;

protected:
    virtual void OnFinish() override;
    virtual void SpawnEnemy();
};
