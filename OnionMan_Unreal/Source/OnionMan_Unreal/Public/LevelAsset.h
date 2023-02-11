// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Wave.h"

#include "LevelAsset.generated.h"

/**
 * 
 */

UCLASS()
class ONIONMAN_UNREAL_API ULevelAsset : public UDataAsset
{
	GENERATED_BODY()

private:
    float m_currentLevelTime = 0.0f;
    float m_currentWaveTime = 0.0f;

    TArray<UWave*> m_waves;

    int m_currentWaveIndex = 0;
    UWave* m_currentWave;

public:
    ULevelAsset(/* args */);

    inline const float CurrentLevelTime() const
    {
        return m_currentLevelTime;
    }
    inline const float CurrentWaveTime() const
    {
        return m_currentWaveTime;
    }

    void Load();

    void Update(float deltaTime);
};
