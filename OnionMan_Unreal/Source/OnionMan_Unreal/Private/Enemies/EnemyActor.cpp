// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyActor.h"
#include "Editor/EditorEngine.h"
#include "UnrealEd.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyActor::TakeDamage(float damageAmount)
{
	CurrentHealth -= damageAmount;
	if (CurrentHealth <= 0)
	{
		// Destroy l'objet ou renvoyer dans la pool
	}
}

void AEnemyActor::DoubleHealth()
{
	MaxHealth = MaxHealth * 2;
}

void AEnemyActor::SetCurrentHealth()
{
	CurrentHealth = MaxHealth;
	LOG_ERROR("CurrentHealth : %f", CurrentHealth);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AEnemyActor::IsAlive() const
{
	LOG_WARNING("Current Health : %f", CurrentHealth);
	return CurrentHealth > 0.0f;
}

void AEnemyActor::Move(float deltaTime, float timeSinceSpawn)
{
}

void AEnemyActor::GetValuesFromActor(AEnemyActor* other)
{
	if (!other)
	{
		LOG_ERROR("Parameter 'other' is null");
		return;
	}

	MaxHealth = other->MaxHealth;
	CurrentHealth = other->CurrentHealth;
	DefaultSpeed = other->DefaultSpeed;
    SpeedFactor = other->SpeedFactor;
    ContactDamage = other->ContactDamage;
    IsArmored = other->IsArmored;
}

void AEnemyActor::Initialize()
{
	if (IsArmored)
	{
		DoubleHealth();
	}

	SetCurrentHealth();
	
	LOG_ERROR("AfterInitialize CurrentHealth : %f", CurrentHealth);
}

void AEnemyActor::KillActor()
{
	CurrentHealth = 0;
	Deactivate();
}

AEnemyActor* AEnemyActor::CloneForEditor()
{
	FActorSpawnParameters Parameters;

	Parameters.Template = this;
	if (UWorld* world = GEditor->GetEditorWorldContext().World())
	{
		if(AEnemyActor* clone = world->SpawnActor<AEnemyActor>(GetClass(), Parameters))
		{
			clone->SetOwner(GetOwner());
			LOG_ERROR("Cloning Actor %s", *GetActorNameOrLabel())

			return clone;
		}
		else
		{
			LOG_ERROR("Failedclone the Actor");
		}
	}
	else
	{
		LOG_ERROR("Failed find the Editor World");
	}
	return nullptr;
}

void AEnemyActor::EditorLoad(float timeSinceSpawn)
{
}

void AEnemyActor::EditorUpdate(float newTimeSinceSpawn)
{
}

void AEnemyActor::EditorUnload()
{
}

void AEnemyActor::EditorSave()
{
}
