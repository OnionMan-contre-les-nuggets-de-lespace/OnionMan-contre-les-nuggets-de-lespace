// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyOnSplineActor.h"

#include "Particles/Collision/ParticleModuleCollisionGPU.h"

void AEnemyOnSplineActor::Spawn(USplineComponent* trajectory)
{
	m_trajectory = trajectory;
}

void AEnemyOnSplineActor::Move(float deltaTime, float timeSinceSpawn)
{
	AEnemyActor::Move(deltaTime, timeSinceSpawn);
	if (IsOnSpline(timeSinceSpawn, m_trajectory))
	{
		SetActorLocation(GetPositionOnSpline(timeSinceSpawn, m_trajectory));
	}
	else
	{
		KillActor();
	}
}

float AEnemyOnSplineActor::GetTimeOnSpline(float timeSinceSpawn)
{
	return timeSinceSpawn * GetSpeed();
}

FVector AEnemyOnSplineActor::GetPositionOnSpline(float timeSinceSpawn, USplineComponent* trajectory)
{
	FVector pos = trajectory->GetLocationAtTime(GetTimeOnSpline(timeSinceSpawn), ESplineCoordinateSpace::World);
	LOG_WARNING("Position at %f : {%d, %d, %d}", GetTimeOnSpline(timeSinceSpawn), pos.X, pos.Y, pos.Z);
	return pos;
}

bool AEnemyOnSplineActor::IsOnSpline(float timeSinceSpawn, USplineComponent* trajectory)
{
	return GetTimeOnSpline(timeSinceSpawn) < trajectory->Duration;
}

void AEnemyOnSplineActor::EditorLoad(float timeSinceSpawn)
{
	AEnemyActor::EditorLoad(timeSinceSpawn);
}

void AEnemyOnSplineActor::EditorLoadOnSpline(float timeSinceSpawn, USplineComponent* trajectory)
{
	EditorLoad(timeSinceSpawn);
	SetActorLocation(GetPositionOnSpline(timeSinceSpawn, trajectory));
}

void AEnemyOnSplineActor::EditorUpdate(float newTimeSinceSpawn)
{
	AEnemyActor::EditorUpdate(newTimeSinceSpawn);
}

void AEnemyOnSplineActor::EditorUpdateOnSpline(float newTimeSinceSpawn, USplineComponent* trajectory)
{
	EditorUpdate(newTimeSinceSpawn);
	bool isOnSpline = IsOnSpline(newTimeSinceSpawn, trajectory);
	SetIsTemporarilyHiddenInEditor(!isOnSpline);
	SetHidden(!isOnSpline);
	if (isOnSpline)
	{
		SetActorLocation(GetPositionOnSpline(newTimeSinceSpawn * DefaultSpeed * SpeedFactor, trajectory));
	}
}

void AEnemyOnSplineActor::EditorUnload()
{
	AEnemyActor::EditorUnload();
}
