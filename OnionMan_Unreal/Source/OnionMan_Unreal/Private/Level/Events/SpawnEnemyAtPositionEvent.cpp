// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyAtPositionEvent.h"

USpawnEnemyAtPositionEvent::USpawnEnemyAtPositionEvent()
{
}

void USpawnEnemyAtPositionEvent::EditorLoad(float timeSinceStart)
{
	USpawnEnemyEvent::EditorLoad(timeSinceStart);

    if(m_isEditorLoaded)
    {
        return;
    }
    // @TODO Display start point

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		// @TODO Instanciate a copy of the enemy
		AIndependantEnemyActor* spawnedEnemy = m_enemyPrefab;

        float spawnTime = GetTime() + i * m_timeBetweenSpawns;
		bool hidden = timeSinceStart < spawnTime;

		spawnedEnemy->SetHidden(hidden);
		spawnedEnnemy->EditorLoadAtPosition(timeSinceStart - spawnTime, m_startPosition);
		if (!hidden)
		{
			spawnedEnnemy->EditorUpdateAtPosition(timeSinceStart - spawnTime, m_startPosition);
		}
		m_editorEnemies.Add(spawnedEnemy);
	}
}

void USpawnEnemyAtPositionEvent::EditorUpdate(float newTimeSinceStart)
{
	USpawnEnemyEvent::EditorUpdate(newTimeSinceStart);

    if(!m_isEditorLoaded)
    {
        return;
    }

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		AIndependantEnemyActor* enemy = m_editorEnemies[i];

        float spawnTime = GetTime() + i * m_timeBetweenSpawns;
		bool hidden = timeSinceStart < spawnTime;

		enemy->SetHidden(hidden);
		if (!hidden)
		{
			enemy->EditorUpdateAtPosition(timeSinceStart - spawnTime, m_startPosition);
		}
		m_editorEnemies.Add(spawnedEnemy);
	}
}

void USpawnEnemyAtPositionEvent::EditorUnload()
{
	USpawnEnemyEvent::EditorUnload();
    if(!m_isEditorLoaded)
    {
        return;
    }
    // @TODO Destroy start point
	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		AIndependantEnemyActor* enemy = m_editorEnemies[i];
		// @TODO Destroy enemy
	}
    m_editorEnemies.Clear();
}

void USpawnEnemyAtPositionEvent::EditorSave()
{
	USpawnEnemyEvent::EditorSave();
    if(!m_isEditorLoaded)
    {
        return;
    }
    // @TODO Save start point position + more is needed
}

AEnemyActor *USpawnEnemyAtPositionEvent::SpawnEnemy()
{
	// Request enemy from pool
	// @TODO : Impl�menter la pool 
	AIndependantEnemyActor* requestedEnemy = m_enemyPrefab;
	requestedEnemy->SetHidden(false);
	requestedEnemy->Spawn(m_startPosition);
	return requestedEnemy;
}
