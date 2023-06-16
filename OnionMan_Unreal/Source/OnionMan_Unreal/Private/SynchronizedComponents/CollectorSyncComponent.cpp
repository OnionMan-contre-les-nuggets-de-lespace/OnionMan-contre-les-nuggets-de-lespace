// Fill out your copyright notice in the Description page of Project Settings.


#include "SynchronizedComponents/CollectorSyncComponent.h"

void UCollectorSyncComponent::LoadProperties()
{
	USynchronizedActorComponent::LoadProperties();
	AddSynchronizedProperty(IsCollectorFull);
}
