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

protected:
    int m_numberOfEnemiesToSpawn = 1;
    float m_timeBetweenSpawns = 0.0f;

    //Cache 
    TArray<SpawnedEnnemy> m_spawnedEnemies;
    int m_spawnedEnemiesCount = 0;
    float m_spawnTimer = 0.0f;

public:
    USpawnEnemyEvent(/* args */);

    virtual void Load() override;
    virtual void Start() override;
    virtual void Update(float deltaTime, float currentWaveTime) override;
    virtual void OnWaveEnd() override;

    // Editor
    virtual void EditorLoad(float timeSinceStart) override;
    virtual void EditorUpdate(float newTimeSinceStart);
    virtual void EditorUnload() override;

    virtual void EditorSave() override;

protected:
    virtual void OnFinish() override;
    virtual AEnemyActor* SpawnEnemy();
};
