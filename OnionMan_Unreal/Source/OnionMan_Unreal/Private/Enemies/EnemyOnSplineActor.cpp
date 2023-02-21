// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyOnSplineActor.h"

void AEnemyOnSplineActor::Spawn(USplineComponent* trajectory)
{
	m_trajectory = trajectory;
}

void AEnemyOnSplineActor::Move(float deltaTime, float timeSinceSpawn)
{
	AEnemyActor::Move(deltaTime, timeSinceSpawn);
}

void AEnemyOnSplineActor::EditorLoad(float timeSinceSpawn)
{
	AEnemyActor::EditorLoad(timeSinceSpawn);
}

void AEnemyOnSplineActor::EditorLoadOnSpline(float timeSinceSpawn, USplineComponent* trajectory)
{
	EditorLoad(timeSinceSpawn);
}

void AEnemyOnSplineActor::EditorUpdate(float newTimeSinceSpawn)
{
	AEnemyActor::EditorUpdate(newTimeSinceSpawn);
}

void AEnemyOnSplineActor::EditorUpdateOnSpline(float newTimeSinceSpawn, USplineComponent* trajectory)
{
	EditorUpdate(newTimeSinceSpawn);
}

void AEnemyOnSplineActor::EditorUnload()
{
	AEnemyActor::EditorUnload();
}
