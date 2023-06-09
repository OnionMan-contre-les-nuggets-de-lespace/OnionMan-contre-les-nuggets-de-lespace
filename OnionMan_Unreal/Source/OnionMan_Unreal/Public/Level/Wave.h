// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Events/BaseWaveEvent.h"

#include "Wave.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API UWave : public UObject
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta = (ShowInnerProperties), DisplayName = "Wave Events")
    TArray<TObjectPtr<UBaseWaveEvent>> m_waveEvents{};

    bool m_isEditorLoaded = false;

private:
    TArray<TObjectPtr<UBaseWaveEvent>> m_eventsThatStarted{};

    int m_eventsCount{};

    bool m_isFinished = false;
    int m_eventToStartIndex = 0;

public:
    UWave(/* args */);

    UFUNCTION(BlueprintCallable)
    inline bool IsFinished()
    {
        return m_isFinished;
    }

    UFUNCTION(BlueprintCallable)
    void Load(AActor* levelAsset);
    UFUNCTION(BlueprintCallable)
    void Update(float deltaTime, float currentWaveTime);
    UFUNCTION(BlueprintCallable)
    void FinishWave();

    // Editor
    UFUNCTION(BlueprintCallable)
    void EditorLoad(float timeSinceWaveStart, AActor* levelAsset);
    UFUNCTION(BlueprintCallable)
    void EditorUpdate(float newTimeSinceWaveStart);
    UFUNCTION(BlueprintCallable)
    void EditorUnload();

    UFUNCTION(BlueprintCallable)
    void EditorSave();
};
