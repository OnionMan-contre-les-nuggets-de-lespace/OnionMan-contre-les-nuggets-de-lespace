// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "LogUtils.h"
#include "Wave.h"

#include "LevelAsset.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API ALevelAsset : public AActor
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, meta = (ShowInnerProperties), DisplayName = "Waves")
    TArray<TObjectPtr<UWave>> m_waves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Wave to Load/Update", Category = "LevelAssetEditor")
    int m_waveToLoad = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Time at Which to reload", Category = "LevelAssetEditor")
    float m_updateTime = 0;

private:
    float m_currentLevelTime = 0.0f;
    float m_currentWaveTime = 0.0f;

    int m_currentWaveIndex = 0;
    TObjectPtr<UWave> m_currentWave = nullptr;

    int m_loadedWave = -1;

public:
    ALevelAsset(/* args */);

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
    bool Update(float deltaTime);

#if WITH_EDITOR
    UFUNCTION(BlueprintCallable)
    void EditorLoad();

    UFUNCTION(BlueprintCallable)
    void EditorUpdate();

    UFUNCTION(BlueprintCallable)
    void EditorUnload();
#endif
};
