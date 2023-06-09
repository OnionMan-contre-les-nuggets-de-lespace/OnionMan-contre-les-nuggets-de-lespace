// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyAtPositionEvent.h"

#include "ObjectPoolActorComponent.h"


USpawnEnemyAtPositionEvent::USpawnEnemyAtPositionEvent()
{
}

void USpawnEnemyAtPositionEvent::EditorLoad(float timeSinceStart, AActor* levelAsset)
{
	USpawnEnemyEvent::EditorLoad(timeSinceStart, levelAsset);

    if(m_isEditorLoaded)
    {
        return;
    }
    // @TODO Display start point

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		AIndependantEnemyActor* spawnedEnemy = (AIndependantEnemyActor*)m_enemyPrefab->CloneForEditor();

        float spawnTime = GetTime() + i * m_timeBetweenSpawns;
		bool hidden = timeSinceStart < spawnTime;

		spawnedEnemy->SetHidden(hidden);
		spawnedEnemy->EditorLoadAtPosition(timeSinceStart - spawnTime, m_startPosition);
		if (!hidden)
		{
			spawnedEnemy->EditorUpdateAtPosition(timeSinceStart - spawnTime, m_startPosition);
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
		bool hidden = newTimeSinceStart < spawnTime;

		enemy->SetHidden(hidden);
		if (!hidden)
		{
			enemy->EditorUpdateAtPosition(newTimeSinceStart - spawnTime, m_startPosition);
		}
		m_editorEnemies.Add(enemy);
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
		enemy->SetHidden(true);
	}
    m_editorEnemies.Empty();
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

TObjectPtr<AEnemyActor> USpawnEnemyAtPositionEvent::SpawnEnemy()
{
	if (UObjectPoolActorComponent* poolComponent = Cast<UObjectPoolActorComponent>(m_enemyPrefab->GetComponentByClass(UObjectPoolActorComponent::StaticClass())))
	{
		if (AIndependantEnemyActor* requestedEnemy = Cast<AIndependantEnemyActor>(poolComponent->SpawnPooledObject()))
		{
			requestedEnemy->SetHidden(false);
			requestedEnemy->Spawn(m_startPosition);
			return requestedEnemy;
		}
	}
	return nullptr;
}
