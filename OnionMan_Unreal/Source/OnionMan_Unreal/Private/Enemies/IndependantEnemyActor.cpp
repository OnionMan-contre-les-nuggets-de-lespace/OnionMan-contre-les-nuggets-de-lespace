// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/IndependantEnemyActor.h"


void AIndependantEnemyActor::Spawn(FVector3f startPosition)
{
}

void AIndependantEnemyActor::Move(float deltaTime, float timeSinceSpawn)
{
    AEnemyActor::Move(deltaTime, timeSinceSpawn);
}

void AIndependantEnemyActor::EditorLoad(float timeSinceSpawn)
{
    AEnemyActor::EditorLoad(timeSinceSpawn);
}

void AIndependantEnemyActor::EditorLoadAtPosition(float timeSinceSpawn, FVector3f startPosition)
{
    EditorLoad(timeSinceSpawn);
}

void AIndependantEnemyActor::EditorUpdate(float newTimeSinceSpawn)
{
    AEnemyActor::EditorUpdate(newTimeSinceSpawn);
}

void AIndependantEnemyActor::EditorUpdateAtPosition(float newTimeSinceSpawn, FVector3f startPosition)
{
    EditorUpdate(newTimeSinceSpawn);
}

void AIndependantEnemyActor::EditorUnload()
{
    AEnemyActor::EditorUnload();
}