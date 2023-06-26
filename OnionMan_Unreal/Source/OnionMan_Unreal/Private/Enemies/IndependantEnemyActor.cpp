// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/IndependantEnemyActor.h"


void AIndependantEnemyActor::Spawn(FVector startPosition)
{
    SetActorLocation(startPosition);
}

void AIndependantEnemyActor::Move(float deltaTime, float timeSinceSpawn)
{
    AEnemyActor::Move(deltaTime, timeSinceSpawn);
}

#if WITH_EDITOR
void AIndependantEnemyActor::EditorLoad(float timeSinceSpawn)
{
    AEnemyActor::EditorLoad(timeSinceSpawn);
}

void AIndependantEnemyActor::EditorLoadAtPosition(float timeSinceSpawn, FVector startPosition)
{
    EditorLoad(timeSinceSpawn);
}

void AIndependantEnemyActor::EditorUpdate(float newTimeSinceSpawn)
{
    AEnemyActor::EditorUpdate(newTimeSinceSpawn);
}

void AIndependantEnemyActor::EditorUpdateAtPosition(float newTimeSinceSpawn, FVector startPosition)
{
    EditorUpdate(newTimeSinceSpawn);
}

void AIndependantEnemyActor::EditorUnload()
{
    AEnemyActor::EditorUnload();
}
#endif