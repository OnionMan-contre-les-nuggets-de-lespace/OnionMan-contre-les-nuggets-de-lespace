// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/SpawnEnemyEvent.h"

USpawnEnemyEvent::USpawnEnemyEvent(/* args */)
{

}


void USpawnEnemyEvent::Load()
{
    UBaseWaveEvent::Load();
    m_spawnedEnemies.Reserve(sizeof(SpawnedEnnemy) * m_numberOfEnemiesToSpawn);
    // Request enemies from pool
}

void USpawnEnemyEvent::Start()
{
    UBaseWaveEvent::Start();
    //Spawn the first one and start a timer to spawn the next ones
}

void USpawnEnemyEvent::Update(float deltaTime, float currentWaveTime)
{
    UBaseWaveEvent::Update(deltaTime, currentWaveTime);
    //Update the position of all spawned enemies
    for (SpawnedEnnemy spawned : m_spawnedEnemies)
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

void USpawnEnemyEvent::EditorLoad(float time)
{
    UBaseWaveEvent::EditorLoad(time);
    // Display the spline

    if (time < GetTime())
    {
        // Display all enemies on the spline
    }
}

void USpawnEnemyEvent::EditorUnload()
{
    UBaseWaveEvent::EditorUnload();
    //Unload all enemies and save the spline
}

void USpawnEnemyEvent::OnFinish()
{
    UBaseWaveEvent::OnFinish();
    //Do nothing maybe
}

void USpawnEnemyEvent::SpawnEnemy()
{

}
