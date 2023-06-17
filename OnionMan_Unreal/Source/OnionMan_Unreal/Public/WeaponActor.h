// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class ONIONMAN_UNREAL_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon");
	float m_baseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon");
	float m_reloadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon");
	float m_reloadTimer;
	UPROPERTY(EditAnywhere, Category = "Weapon");
	uint16 m_id;

	// Sets default values for this actor's properties
	AWeaponActor();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool TryShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
