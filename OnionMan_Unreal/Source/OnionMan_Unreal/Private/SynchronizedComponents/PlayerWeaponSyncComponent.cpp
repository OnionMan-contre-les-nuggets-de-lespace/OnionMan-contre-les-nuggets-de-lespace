// Fill out your copyright notice in the Description page of Project Settings.


#include "SynchronizedComponents/PlayerWeaponSyncComponent.h"

void UPlayerWeaponSyncComponent::LoadProperties()
{
	USynchronizedActorComponent::LoadProperties();
	AddSynchronizedProperty(CurrentWeapon);
}
