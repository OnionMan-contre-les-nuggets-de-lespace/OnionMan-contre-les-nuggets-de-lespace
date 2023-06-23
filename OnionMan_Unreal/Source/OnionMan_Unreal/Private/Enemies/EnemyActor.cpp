// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyActor.h"

#include "MathUtil.h"
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
		KillActor(true);
	}
}

void AEnemyActor::DoubleHealth()
{
	MaxHealth = MaxHealth * 2;
}

void AEnemyActor::SetCurrentHealth()
{
	CurrentHealth = MaxHealth;
	LOG_ERROR("SET CurrentHealth : %f", CurrentHealth);
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
	SetActorScale3D(other->GetActorScale());
	SetActorRotation(other->GetActorRotation());

	WeaponPartBP = other->WeaponPartBP;
	ChanceToSpawnWeaponPart = other->ChanceToSpawnWeaponPart;
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

void AEnemyActor::KillActor(bool killedByPlayer)
{
	CurrentHealth = 0;

	if (killedByPlayer)
	{
		LOG_ERROR("Killed Actor %s", *GetActorNameOrLabel());
		if (FMath::RandRange(0.0f, 1.0f) <= ChanceToSpawnWeaponPart)
		{
			UWorld* const World = GetWorld();
			if (World && WeaponPartBP)
			{
				FVector actorLocation = GetActorLocation();
				World->SpawnActor<AActor>(WeaponPartBP, actorLocation, FRotator().ZeroRotator);
				LOG_ERROR("Spawned a WeaponPart at {%f, %f, %f}", actorLocation.X, actorLocation.Y, actorLocation.Z);
			}
		}
	}
	
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
