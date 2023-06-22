// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	
}


void APooledObject::SetActive(bool IsActive)
{
    Active = IsActive;
    SetActorHiddenInGame(!IsActive);
    GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Deactivate, LifeSpan, false);
}

void APooledObject::SetLifeSpan(float LifeTime)
{
    LifeSpan = LifeTime;
}

void APooledObject::SetPoolIndex(int Index)
{
    PoolIndex = Index;
}

void APooledObject::BeginPlay()
{
    AActor::BeginPlay();
 	SetActorLocation(DisabledObjectsPosition);
}

void APooledObject::Deactivate()
{
    SetActive(false);
    GetWorldTimerManager().ClearAllTimersForObject(this);
    OnPooledObjectDespawned.Broadcast(this);
    SetActorLocation(DisabledObjectsPosition);
}

bool APooledObject::IsActive()
{
    return Active;
}

int APooledObject::GetPoolIndex()
{
    return PoolIndex;
}

