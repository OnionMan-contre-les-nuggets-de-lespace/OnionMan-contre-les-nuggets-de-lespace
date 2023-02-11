// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyOnSplineActor.h"

void AEnemyOnSplineActor::Spawn(USplineComponent* trajectory)
{
	m_trajectory = trajectory;
}

void AEnemyOnSplineActor::Move(float deltaTime, float timeSinceSpawn)
{
}

void AEnemyOnSplineActor::EditorLoad(float timeSinceSpawn)
{
}

void AEnemyOnSplineActor::EditorUpdate(float newTimeSinceSpawn)
{
}

void AEnemyOnSplineActor::EditorUnload()
{
}
