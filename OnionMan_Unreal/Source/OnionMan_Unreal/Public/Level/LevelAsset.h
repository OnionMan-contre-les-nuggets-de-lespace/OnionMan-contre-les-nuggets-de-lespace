// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Wave.h"

#include "LevelAsset.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API ULevelAsset : public UDataAsset
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta = (ShowInnerProperties), DisplayName = "Waves")
        TArray<TObjectPtr<UWave>> m_waves;

private:
    float m_currentLevelTime = 0.0f;
    float m_currentWaveTime = 0.0f;

    int m_currentWaveIndex = 0;
    TObjectPtr<UWave> m_currentWave;

public:
    ULevelAsset(/* args */);

    UFUNCTION(BlueprintCallable)
    inline float CurrentLevelTime() const
    {
        return m_currentLevelTime;
    }

    UFUNCTION(BlueprintCallable)
    inline float CurrentWaveTime() const
    {
        return m_currentWaveTime;
    }

    UFUNCTION(BlueprintCallable)
    void Load();

    UFUNCTION(BlueprintCallable)
    void Update(float deltaTime);
};
