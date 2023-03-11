// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyEvent.h"

USpawnEnemyEvent::USpawnEnemyEvent(/* args */)
{

}


void USpawnEnemyEvent::Load()
{
    UBaseWaveEvent::Load();
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
    //Spawn the new enemies
    if (m_spawnedEnemiesCount < m_numberOfEnemiesToSpawn) 
    {
        if (m_spawnTimer >= m_timeBetweenSpawns) 
        {
            m_spawnTimer = 0;
            TObjectPtr<AEnemyActor> newEnemy = SpawnEnemy();
            m_spawnedEnemies.Add(SpawnedEnemy{ newEnemy, currentWaveTime });
            m_spawnedEnemiesCount++;
        }
        m_spawnTimer += deltaTime;
    }

    //Update the position of all spawned enemies
    for (SpawnedEnemy spawned : m_spawnedEnemies)
    {
        if (spawned.Enemy()->IsAlive())
        {
            spawned.Enemy()->Move(deltaTime, currentWaveTime - spawned.SpawnTime());
        }
    }
}

void USpawnEnemyEvent::OnWaveEnd()
{
    UBaseWaveEvent::OnWaveEnd();
    //Release the enemies
}

void USpawnEnemyEvent::EditorLoad(float timeSinceStart)
{
    UBaseWaveEvent::EditorLoad(timeSinceStart);
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
    UBaseWaveEvent::EditorUnload();
    if(!m_isEditorLoaded)
    {
        return;
    }
    //Unload all enemies
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
