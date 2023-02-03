// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyActor::TakeDamage(float DamageAmount)
{
	m_currentHealth -= DamageAmount;
	if (m_currentHealth <= 0)
	{
		// Destroy l'objet ou renvoyer dans la pool
	}
}

void AEnemyActor::DoubleHealth()
{
	m_maxHealth = m_maxHealth * 2;
}

void AEnemyActor::SetCurrentHealt()
{
	m_currentHealth = m_maxHealth;
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsArmored)
	{
		DoubleHealth();
	}

	SetCurrentHealt();
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

