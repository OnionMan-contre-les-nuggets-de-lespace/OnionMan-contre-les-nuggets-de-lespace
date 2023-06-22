// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyOnSplineEvent.h"

#include "ObjectPoolActorComponent.h"
#include "Editor/EditorEngine.h"
#include "UnrealEd.h"

USpawnEnemyOnSplineEvent::USpawnEnemyOnSplineEvent()
{
}

USpawnEnemyOnSplineEvent::~USpawnEnemyOnSplineEvent()
{
	DestroyEditorActors();
}

void USpawnEnemyOnSplineEvent::EditorLoad(float timeSinceStart, AActor* levelAsset)
{
	USpawnEnemyEvent::EditorLoad(timeSinceStart, levelAsset);

	Initialize();
	if (!m_initilizedSuccessfully) 
	{
		return;
	}
	m_enemyPrefab->SetIsTemporarilyHiddenInEditor(true);
	for (int i{ 0 }; i < m_numberOfEnemiesToSpawn; i++)
	{
		AEnemyOnSplineActor* spawnedEnemy = (AEnemyOnSplineActor*) m_enemyPrefab->CloneForEditor();

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

	if (m_numberOfEnemiesToSpawn != m_editorEnemies.Num()) 
	{
		DestroyEditorActors();

		for (int i{ 0 }; i < m_numberOfEnemiesToSpawn; i++)
		{
			AEnemyOnSplineActor* spawnedEnemy = (AEnemyOnSplineActor*)m_enemyPrefab->CloneForEditor();
			m_editorEnemies.Add(spawnedEnemy);
		}
	}

	for (int i {0}; i < m_numberOfEnemiesToSpawn; i++)
	{
		if (AEnemyOnSplineActor* enemy = m_editorEnemies[i]) 
		{
			float spawnTime = GetTime() + i * m_timeBetweenSpawns;
			bool hidden = newTimeSinceStart < spawnTime;

			enemy->SetHidden(hidden);
			if (!hidden)
			{
				enemy->EditorUpdateOnSpline(newTimeSinceStart - spawnTime, m_spline);
			}
		}
	}
}

void USpawnEnemyOnSplineEvent::EditorUnload()
{
	LOG_ERROR("USpawnEnemyOnSplineEvent::EditorUnload")
    if(!m_isEditorLoaded)
    {
		LOG_ERROR("EditorNotLoaded")
        return;
    }

	DestroyEditorActors();
	m_enemyPrefab->SetIsTemporarilyHiddenInEditor(false);
	
	USpawnEnemyEvent::EditorUnload();
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

void USpawnEnemyOnSplineEvent::DestroyEditorActors()
{
	LOG_ERROR("DestroyEditorActors")
	for (int i{ 0 }; i < m_editorEnemies.Num(); i++)
	{
		if (AEnemyOnSplineActor* enemy = m_editorEnemies[i]) 
		{
			enemy->EditorUnload();
			
			enemy->GetWorld()->DestroyActor(enemy);
			LOG_ERROR("Destroyed actor (in theory)")
		}
	}
	m_editorEnemies.Empty();
}

TObjectPtr<AEnemyActor> USpawnEnemyOnSplineEvent::SpawnEnemy()
{
	LOG_ERROR("USpawnEnemyOnSplineEvent::SpawnEnemy()")
	Initialize();
	if (!m_initilizedSuccessfully)
	{
		return nullptr;
	}
	if (UObjectPoolActorComponent* poolComponent = Cast<UObjectPoolActorComponent>(m_enemyPrefab->GetComponentByClass(UObjectPoolActorComponent::StaticClass())))
	{
		if (AEnemyOnSplineActor* requestedEnemy = Cast<AEnemyOnSplineActor>(poolComponent->SpawnPooledObject()))
		{
			requestedEnemy->SetHidden(false);
			requestedEnemy->Spawn(m_spline);
			requestedEnemy->GetValuesFromActor(m_enemyPrefab);
			
			return requestedEnemy;
		}
		LOG_ERROR("Could not cast the requested ennemy to AEnemyOnSplineActor");
	}
	else
	{
		LOG_ERROR("Could not get the poolComponent from the prefab");
	}
	return nullptr;
}

void USpawnEnemyOnSplineEvent::Initialize()
{
	if (m_initilizedSuccessfully) 
	{
		return;
	}

	if (!m_levelAsset)
	{
		LOG_ERROR("LevelAsset is Null");
		return;
	}

	if (USplineComponent* splineComponent = Cast<USplineComponent>(m_splineComponent.ExtractComponent(m_levelAsset)))
	{
		if (UChildActorComponent* childActorComponent = Cast<UChildActorComponent>(m_childActorComponent.ExtractComponent(m_levelAsset)))
		{
			if (AEnemyOnSplineActor* enemyOnSpline = Cast<AEnemyOnSplineActor>(childActorComponent->GetChildActor()))
			{
				m_enemyPrefab = enemyOnSpline;
				m_enemyPrefab->SetHidden(true);
				m_spline = splineComponent;

				m_initilizedSuccessfully = true;
			}
			else
			{
				LOG_ERROR("Failed to cast EnemyOnSplineActor");
			}
		}
		else
		{
			LOG_ERROR("Failed to cast ChildActorComponent");
		}
	}
	else
	{
		LOG_ERROR("Failed to cast SplineComponent");
	}
	LOG_ERROR("Initialized Successfully %s", m_initilizedSuccessfully ? *FString("True") : *FString("False"));
}


