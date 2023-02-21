// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyOnSplineEvent.h"

USpawnEnemyOnSplineEvent::USpawnEnemyOnSplineEvent()
{
}

void USpawnEnemyOnSplineEvent::EditorLoad(float timeSinceStart)
{
	USpawnEnemyEvent::EditorLoad(timeSinceStart);

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		// @TODO Instanciate a copy of the enemy
		AEnemyOnSplineActor* spawnedEnemy = m_enemyPrefab;

        float spawnTime = GetTime() + i * m_timeBetweenSpawns;
		bool hidden = timeSinceStart < GetTime() + spawnTime;

		spawnedEnemy->SetHidden(hidden);
		spawnedEnemy->EditorLoadOnSpline(timeSinceStart - spawnTime, m_spline);
		if (!hidden)
		{
			spawnedEnemy->EditorUpdateOnSpline(timeSinceStart - spawnTime, m_spline);
		}
		m_editorEnemies.Add(spawnedEnemy);
	}
}

void USpawnEnemyOnSplineEvent::EditorUpdate(float newTimeSinceStart)
{
	USpawnEnemyEvent::EditorUpdate(newTimeSinceStart);
    if(!m_isEditorLoaded)
    {
        return;
    }

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		AEnemyOnSplineActor* enemy = m_editorEnemies[i];

        float spawnTime = GetTime() + i * m_timeBetweenSpawns;
		bool hidden = newTimeSinceStart < spawnTime;

		enemy->SetHidden(hidden);
		if (!hidden)
		{
			enemy->EditorUpdateOnSpline(newTimeSinceStart - spawnTime, m_spline);
		}
	}
}

void USpawnEnemyOnSplineEvent::EditorUnload()
{
	USpawnEnemyEvent::EditorUnload();
    if(!m_isEditorLoaded)
    {
        return;
    }

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		AEnemyOnSplineActor* enemy = m_editorEnemies[i];
		// @TODO Destroy Enemy
	}
	m_editorEnemies.Empty();
}

void USpawnEnemyOnSplineEvent::EditorSave()
{
	USpawnEnemyEvent::EditorSave();
    if(!m_isEditorLoaded)
    {
        return;
    }
	// @TODO Save Spline
}

AEnemyActor* USpawnEnemyOnSplineEvent::SpawnEnemy()
{
	// Request enemy from pool
	// @TODO : Impl�menter la pool 
	AEnemyOnSplineActor* requestedEnemy = m_enemyPrefab;
	requestedEnemy->SetHidden(false);
	requestedEnemy->Spawn(m_spline);
	return requestedEnemy;
}
