// Fill out your copyright notice in the Description page of Project Settings.


#include "SynchronizedComponents/GameStateSyncComponent.h"

void UGameStateSyncComponent::LoadProperties()
{
	USynchronizedActorComponent::LoadProperties();
	AddSynchronizedProperty(GameState);
}


