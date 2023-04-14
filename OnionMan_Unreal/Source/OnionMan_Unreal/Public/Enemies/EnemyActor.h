// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class ONIONMAN_UNREAL_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float m_maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float m_currentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float m_defaultSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float m_speedFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float m_contactDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		bool IsArmored;
	// Create Property Weapons ! (donc un script C++ weapon)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<AActor> Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		TSubclassOf<AActor> m_actorBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Options")
		TSubclassOf<AActor> m_objectPoolBP;
	/*UFUNCTION(BlueprintCallable, Category = "Enemy")
		void SpawnActor(FVector Location);*/

	UFUNCTION(BlueprintCallable, Category = "Enemy")
		void TakeDamage(float DamageAmount);

	bool IsAlive();

	virtual void Move(float deltaTime, float timeSinceSpawn);


	// Editor
	virtual void EditorLoad(float timeSinceSpawn);
	virtual void EditorUpdate(float newTimeSinceSpawn);
	virtual void EditorUnload();

	virtual void EditorSave(); // Possibly useless

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DoubleHealth();
	void SetCurrentHealt();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
