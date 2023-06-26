// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseWaveEvent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API UBaseWaveEvent : public UObject
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, DisplayName = "Time")
    float m_time = 0.0f;

    AActor* m_levelAsset = nullptr;

private:
    bool m_isFinished = false;

    // Editor
protected:
    bool m_isEditorLoaded = false;

public:
    UBaseWaveEvent(/* args */);

    UFUNCTION(BlueprintCallable)
    inline float GetTime()
    {
        return m_time;
    }

    UFUNCTION(BlueprintCallable)
    inline bool IsFinished()
    {
        return m_isFinished;
    }

    UFUNCTION(BlueprintCallable)
    virtual void Load(AActor* levelAsset);
    UFUNCTION(BlueprintCallable)
    virtual void Start();
    UFUNCTION(BlueprintCallable)
    virtual void Update(float deltaTime, float currentWaveTime);
    UFUNCTION(BlueprintCallable)
    virtual void OnWaveEnd();

    // Editor
#if WITH_EDITOR
    UFUNCTION(BlueprintCallable)
    virtual void EditorLoad(float timeSinceStart, AActor* levelAsset);
    UFUNCTION(BlueprintCallable)
    virtual void EditorUpdate(float newTimeSinceWaveStart);
    UFUNCTION(BlueprintCallable)
    virtual void EditorUnload();
    UFUNCTION(BlueprintCallable)
    virtual void EditorSave();
#endif

protected:
    UFUNCTION(BlueprintCallable)
    void Finish();
    UFUNCTION(BlueprintCallable)
    virtual void OnFinish();
};
