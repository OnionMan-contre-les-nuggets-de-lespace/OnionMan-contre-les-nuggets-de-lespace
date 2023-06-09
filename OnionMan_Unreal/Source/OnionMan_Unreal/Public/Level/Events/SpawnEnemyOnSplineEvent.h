// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/Events/SpawnEnemyEvent.h"
#include "../../Enemies/EnemyOnSplineActor.h"
#include "Components/SplineComponent.h"
#include "SpawnEnemyOnSplineEvent.generated.h"

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API USpawnEnemyOnSplineEvent : public USpawnEnemyEvent
{
	GENERATED_BODY()
protected:

	UPROPERTY(
		EditAnywhere, 
		DisplayName = "Spline", 
		BlueprintReadWrite, 
		meta = (UseComponentPicker, AllowedClasses = "/Script/Engine.SplineComponent"))
    FComponentReference m_splineComponent;

	UPROPERTY(
		EditAnywhere,
		DisplayName = "Enemy Prefab",
		BlueprintReadWrite, 
		meta = (UseComponentPicker, AllowedClasses = "/Script/Engine.ChildActorComponent"))
	FComponentReference m_childActorComponent;
	

	TArray<AEnemyOnSplineActor*> m_editorEnemies;

private:
	bool m_initilizedSuccessfully = false;

	AEnemyOnSplineActor* m_enemyPrefab = nullptr;
	USplineComponent* m_spline = nullptr;


public:
	USpawnEnemyOnSplineEvent(/* args */);
	~USpawnEnemyOnSplineEvent();

    // Editor
    virtual void EditorLoad(float timeSinceStart, AActor* levelAsset) override;
    virtual void EditorUpdate(float newTimeSinceStart) override;
    virtual void EditorUnload() override;

    virtual void EditorSave() override;

	void DestroyEditorActors();

protected:
	virtual TObjectPtr<AEnemyActor> SpawnEnemy() override;

private:
	void Initialize();
};
