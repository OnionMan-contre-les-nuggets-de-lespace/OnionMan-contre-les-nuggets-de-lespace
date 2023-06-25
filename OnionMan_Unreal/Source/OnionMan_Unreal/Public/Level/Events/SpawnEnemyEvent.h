// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseWaveEvent.h"
#include "Enemies/EnemyActor.h"

#include "SpawnEnemyEvent.generated.h"

struct SpawnedEnemy
{
private:
    TObjectPtr<AEnemyActor> m_enemyObject;
    float m_spawnTime;

public:
    SpawnedEnemy(TObjectPtr<AEnemyActor> enemy, float spawnTime)
    {
        m_enemyObject = enemy;
        m_spawnTime = spawnTime;
    }

    TObjectPtr<AEnemyActor> Enemy() const
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
    UPROPERTY(EditAnywhere, DisplayName = "Number of Enemies to Spawn")
    int m_numberOfEnemiesToSpawn = 1;
    UPROPERTY(EditAnywhere, DisplayName = "Time Between Spawns")
    float m_timeBetweenSpawns = 0.0f;

    //Cache 
    TArray<SpawnedEnemy> m_spawnedEnemies;
    int m_spawnedEnemiesCount = 0;
    float m_spawnTimer = 0.0f;

public:
    USpawnEnemyEvent(/* args */);

    virtual void Load(AActor* levelAsset) override;
    virtual void Start() override;
    virtual void Update(float deltaTime, float currentWaveTime) override;
    virtual void OnWaveEnd() override;

    // Editor
#if WITH_EDITOR
    virtual void EditorLoad(float timeSinceStart, AActor* levelAsset) override;
    virtual void EditorUpdate(float newTimeSinceStart) override;
    virtual void EditorUnload() override;

    virtual void EditorSave() override;
#endif

protected:
    virtual void OnFinish() override;
    virtual TObjectPtr<AEnemyActor> SpawnEnemy();
};
