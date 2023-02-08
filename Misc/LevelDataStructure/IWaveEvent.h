// Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"

class IWaveEvent
{

private:
    float m_time = 0.0f;
    bool m_isFinished = false;

public:
    IWaveEvent(/* args */);
    ~IWaveEvent();

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
    virtual void Update(float deltaTime);
    virtual void OnWaveEnd();

    // Editor
    virtual void EditorLoad(float time);
    virtual void EditorUnload();

protected:
    void Finish();
    virtual void OnFinish();
};

IWaveEvent::IWaveEvent(/* args */)
{
    m_isFinished = false;
}

IWaveEvent::~IWaveEvent()
{
}

void IWaveEvent::Load()
{
    m_isFinished = false;
}

void IWaveEvent::Start()
{
}

void IWaveEvent::Update(float deltaTime)
{
}

void IWaveEvent::OnWaveEnd()
{
}

void IWaveEvent::EditorLoad(float time)
{
}

void IWaveEvent::EditorUnload()
{
}

void IWaveEvent::Finish()
{
    m_isFinished = true;
    OnFinish();
}

void IWaveEvent::OnFinish()
{
}
