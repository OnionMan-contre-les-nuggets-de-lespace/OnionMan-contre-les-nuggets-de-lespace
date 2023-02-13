// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Events/BaseWaveEvent.h"

#include "Wave.generated.h"

/**
 * 
 */

UCLASS()
class ONIONMAN_UNREAL_API UWave : public UObject
{
	GENERATED_BODY()
private:
    TArray<UBaseWaveEvent*> m_waveEvents;

    TArray<UBaseWaveEvent*> m_eventsThatStarted;

    bool m_isFinished = false;
    int m_eventToStartIndex = 0;

public:
    UWave(/* args */);

    inline bool IsFinished()
    {
        return m_isFinished;
    }

    void Load();
    void Update(float deltaTime, float currentWaveTime);
    void FinishWave();

    // Editor
    void EditorLoad(float time);
    void EditorUnload();
};
