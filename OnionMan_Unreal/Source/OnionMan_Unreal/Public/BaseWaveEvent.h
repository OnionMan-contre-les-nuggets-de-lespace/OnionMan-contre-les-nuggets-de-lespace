// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BaseWaveEvent.generated.h"

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API UBaseWaveEvent : public UObject
{
	GENERATED_BODY()

private:
    float m_time = 0.0f;
    bool m_isFinished = false;

public:
    UBaseWaveEvent(/* args */);

    inline float GetTime()
    {
        return m_time;
    }

    inline bool IsFinished()
    {
        return m_isFinished;
    }

    virtual void Load();
    virtual void Start();
    virtual void Update(float deltaTime, float currentWaveTime);
    virtual void OnWaveEnd();

    // Editor
    virtual void EditorLoad(float time);
    virtual void EditorUnload();

protected:
    void Finish();
    virtual void OnFinish();
};
