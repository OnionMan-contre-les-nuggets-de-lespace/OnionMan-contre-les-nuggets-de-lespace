// Fill out your copyright notice in the Description page of Project Settings.


#include "SynchronizedComponents/BeamSyncComponent.h"

void UBeamSyncComponent::LoadProperties()
{
	USynchronizedActorComponent::LoadProperties();
	AddSynchronizedProperty(BeamPhaseReached);
	AddSynchronizedProperty(BeamIsReady);
}
