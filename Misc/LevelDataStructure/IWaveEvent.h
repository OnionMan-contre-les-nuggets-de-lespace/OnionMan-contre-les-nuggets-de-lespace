// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class IWaveEvent
{
private:
    float m_time = 0.0f;
    bool m_isFinished = false;

public:
    IWaveEvent(/* args */);
    ~IWaveEvent();

    inline bool IsFinished()
    {
        return m_isFinished;
    }

    virtual void Load();
    virtual void Update();

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
}

void IWaveEvent::Update()
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
