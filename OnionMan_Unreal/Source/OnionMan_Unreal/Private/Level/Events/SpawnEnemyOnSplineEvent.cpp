// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyOnSplineEvent.h"

USpawnEnemyOnSplineEvent::USpawnEnemyOnSplineEvent()
{
}

void USpawnEnemyOnSplineEvent::EditorLoad(float timeSinceStart)
{
	USpawnEnemyEvent::EditorLoad(timeSinceStart);

	Initialize();
	if (!m_initilizedSuccessfully) 
	{
		return;
	}

	for (int i{ 0 }; i < m_numberOfEnemiesToSpawn; i++)
	{
		AEnemyOnSplineActor* spawnedEnemy = (AEnemyOnSplineActor*) m_enemyPrefab->Clone();

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
		enemy->SetHidden(true);
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
	//m_spline->GetSplinePointsPosition().Points[0].
	// @TODO Save Spline
}

TObjectPtr<AEnemyActor> USpawnEnemyOnSplineEvent::SpawnEnemy()
{
	Initialize();
	if (!m_initilizedSuccessfully)
	{
		return nullptr;
	}

	AEnemyOnSplineActor* requestedEnemy = (AEnemyOnSplineActor*)m_enemyPrefab->Clone();
	requestedEnemy->SetHidden(false);
	requestedEnemy->Spawn(m_spline);
	return requestedEnemy;
}

void USpawnEnemyOnSplineEvent::Initialize()
{
	if (m_initilizedSuccessfully) 
	{
		return;
	}

	if (USplineComponent* splineComponent = Cast<USplineComponent>(m_splineComponent.GetComponent((m_splineComponent.OtherActor).Get())))
	{
		if (UChildActorComponent* childActorComponent = Cast<UChildActorComponent>(m_childActorComponent.GetComponent((m_childActorComponent.OtherActor).Get())))
		{
			if (AEnemyOnSplineActor* enemyOnSpline = Cast<AEnemyOnSplineActor>(childActorComponent->GetChildActor()))
			{
				m_enemyPrefab = enemyOnSpline;
				m_spline = splineComponent;

				m_initilizedSuccessfully = true;
			}
		}
	}
}


