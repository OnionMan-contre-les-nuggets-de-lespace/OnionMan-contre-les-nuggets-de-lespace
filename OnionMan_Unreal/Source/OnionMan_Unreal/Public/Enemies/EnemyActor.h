// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"
#include "GameFramework/Actor.h"
#include "LogUtils.h"
#include "EnemyActor.generated.h"

UCLASS()
class ONIONMAN_UNREAL_API AEnemyActor : public APooledObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float MaxHealth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float CurrentHealth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float DefaultSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float SpeedFactor = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float ContactDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		bool IsArmored = false;
	// Create Property Weapons ! (donc un script C++ weapon)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<AActor> Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<AActor> m_actorBP;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Options")
	// 	TSubclassOf<AActor> m_objectPoolBP;
	/*UFUNCTION(BlueprintCallable, Category = "Enemy")
		void SpawnActor(FVector Location);*/

	UFUNCTION(BlueprintCallable, Category = "Enemy")
		void TakeDamage(float DamageAmount);

	bool IsAlive() const;

	inline float GetSpeed() const
	{
		return DefaultSpeed* SpeedFactor;
	}

	virtual void Move(float deltaTime, float timeSinceSpawn);
	virtual void GetValuesFromActor(AEnemyActor* other);
	virtual void Initialize();
	virtual void KillActor();

	AEnemyActor* CloneForEditor();


	// Editor
	virtual void EditorLoad(float timeSinceSpawn);
	virtual void EditorUpdate(float newTimeSinceSpawn);
	virtual void EditorUnload();

	virtual void EditorSave(); // Possibly useless

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DoubleHealth();
	void SetCurrentHealth();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
