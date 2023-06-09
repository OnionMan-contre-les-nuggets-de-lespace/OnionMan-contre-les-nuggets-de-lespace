// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyEvent.h"

USpawnEnemyEvent::USpawnEnemyEvent(/* args */)
{

}


void USpawnEnemyEvent::Load(AActor* levelAsset)
{
    UBaseWaveEvent::Load(levelAsset);
    m_spawnedEnemies.Reserve(sizeof(SpawnedEnemy) * m_numberOfEnemiesToSpawn);
    // Request enemies from pool
}

void USpawnEnemyEvent::Start()
{
    UBaseWaveEvent::Start();
    //Spawn the first one and start a timer to spawn the next ones
    m_spawnTimer = m_timeBetweenSpawns;
}

void USpawnEnemyEvent::Update(float deltaTime, float currentWaveTime)
{
    UBaseWaveEvent::Update(deltaTime, currentWaveTime);
    LOG_ERROR("Event Update");
    //Spawn the new enemies
    if (m_spawnedEnemiesCount < m_numberOfEnemiesToSpawn) 
    {
        if (m_spawnTimer >= m_timeBetweenSpawns) 
        {
            m_spawnTimer = 0;
            if (const TObjectPtr<AEnemyActor> newEnemy = SpawnEnemy())
            {
                newEnemy->Initialize();
                newEnemy->SetHidden(false);
                m_spawnedEnemies.Add(SpawnedEnemy{ newEnemy, currentWaveTime });
                m_spawnedEnemiesCount++;
            }
        }
        m_spawnTimer += deltaTime;
    }

    //Update the position of all spawned enemies
    bool noEnemiesAlive = true;
    for (SpawnedEnemy spawned : m_spawnedEnemies)
    {
        if (spawned.Enemy())
        {
            if (spawned.Enemy()->IsAlive())
            {
                LOG_WARNING("Moving Enemy");
                LOG_WARNING("IsHidden : %s", spawned.Enemy()->IsHidden() ? *FString("True") : *FString("False"))
                spawned.Enemy()->Move(deltaTime, currentWaveTime - spawned.SpawnTime());
                noEnemiesAlive = false;
            }
            else
            {
                LOG_ERROR("Enemy is not alive");
            }
        }
        else
        {
            LOG_ERROR("Enemy is Null");
        }
    }

    if (m_spawnedEnemiesCount == m_numberOfEnemiesToSpawn && noEnemiesAlive)
    {
        Finish();
    }
}

void USpawnEnemyEvent::OnWaveEnd()
{
    UBaseWaveEvent::OnWaveEnd();
    //Release the enemies
}

void USpawnEnemyEvent::EditorLoad(float timeSinceStart, AActor* levelAsset)
{
    UBaseWaveEvent::EditorLoad(timeSinceStart, levelAsset);
    // Display the spline
    if(m_isEditorLoaded)
    {
        return;
    }
}

void USpawnEnemyEvent::EditorUpdate(float newTimeSinceStart)
{
    UBaseWaveEvent::EditorUpdate(newTimeSinceStart);
    if(!m_isEditorLoaded)
    {
        return;
    }
}

void USpawnEnemyEvent::EditorUnload()
{
    if(!m_isEditorLoaded)
    {
        return;
    }
    //Unload all enemies
    UBaseWaveEvent::EditorUnload();
}

void USpawnEnemyEvent::EditorSave()
{
    UBaseWaveEvent::EditorSave();
    if(!m_isEditorLoaded)
    {
        return;
    }
    // Save values
}

void USpawnEnemyEvent::OnFinish()
{
    UBaseWaveEvent::OnFinish();
    //Do nothing maybe
}

TObjectPtr<AEnemyActor> USpawnEnemyEvent::SpawnEnemy()
{
    return nullptr;
}
