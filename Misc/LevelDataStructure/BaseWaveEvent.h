// Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"

class BaseWaveEvent
{
protected:
    ULevelAsset* m_levelAsset;
private:
    float m_time = 0.0f;
    bool m_isFinished = false;

public:
    BaseWaveEvent(/* args */);
    ~BaseWaveEvent();

    inline float GetTime()
    {
        return m_time;
    }

    inline bool IsFinished()
    {
        return m_isFinished;
    }
    
    virtual void Load(ULevelAsset* level);
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void OnWaveEnd();

    // Editor
    virtual void EditorLoad(float time);
    virtual void EditorUnload();

protected:
    void Finish();
    virtual void OnFinish();
};

BaseWaveEvent::BaseWaveEvent(/* args */)
{
    m_isFinished = false;
}

BaseWaveEvent::~BaseWaveEvent()
{
}

void BaseWaveEvent::Load(ULevelAsset* level)
{
    m_levelAsset = level;
    m_isFinished = false;
}

void BaseWaveEvent::Start()
{
}

void BaseWaveEvent::Update(float deltaTime)
{
}

void BaseWaveEvent::OnWaveEnd()
{
}

void BaseWaveEvent::EditorLoad(float time)
{
}

void BaseWaveEvent::EditorUnload()
{
}

void BaseWaveEvent::Finish()
{
    m_isFinished = true;
    OnFinish();
}

void BaseWaveEvent::OnFinish()
{
}
