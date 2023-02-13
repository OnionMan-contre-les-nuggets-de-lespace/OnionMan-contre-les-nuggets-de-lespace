// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/SpawnEnemyOnSplineEvent.h"

USpawnEnemyOnSplineEvent::USpawnEnemyOnSplineEvent()
{
}

AEnemyActor* USpawnEnemyOnSplineEvent::SpawnEnemy()
{
	// Request enemy from pool
	// @TODO : Implémenter la pool 
	AEnemyOnSplineActor* requestedEnemy = m_enemyPrefab;
	requestedEnemy->SetHidden(false);
	requestedEnemy->Spawn(m_spline);
	return requestedEnemy;
}
