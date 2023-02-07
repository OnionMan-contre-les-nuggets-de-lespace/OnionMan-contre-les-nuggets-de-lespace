// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWaveEvent.h"
#include "LevelAsset.h"

class Wave
{
private:
    TArray<IWaveEvent*> m_waveEvents;

    TArray<IWaveEvent*> m_eventsThatStarted;

    ULevelAsset* m_levelAsset

    bool m_isFinished = false;
    int m_eventToStartIndex = 0;

public:
    Wave(/* args */);
    ~Wave();

    inline bool IsFinished()
    {
        return m_isFinished;
    }

    void Load();
    void Update(float deltaTime);
    void FinishWave();
};

Wave::Wave(/* args */)
{
    m_isFinished = false;
}

Wave::~Wave()
{
}

void Wave::Load(ULevelAsset* level)
{
    m_levelAsset = level;

    m_waveEvents.Sort([](IWaveEvent* event1, IWaveEvent* event2){event1->GetTime() < event2->GetTime()});

    for (IWaveEvent* event : m_waveEvents)
    {
        event->Load();
    }
}

void Wave::Update(float deltaTime)
{
    while (m_levelAsset->CurrentTime() >= m_waveEvents[m_eventToStartIndex]->GetTime())
    {
        IWaveEvent* eventToStart = m_waveEvents[m_eventToStartIndex];
        m_eventsThatStarted.Add(eventToStart);

        eventToStart->Start();


        m_eventToStartIndex++;
    }

    bool allEventFinished = true;
    for (IWaveEvent* event : m_eventThatStarted)
    {
        if (event->IsFinished())
        {
            continue;
        }
        allEventFinished = false;
        event->Update(deltaTime);
    }

    if (allEventFinished && m_eventThatStarted.Num() == m_waveEvents.Num()) // All events started and finished
    {
        m_isFinished = true;
    }
    
}

inline void Wave::FinishWave()
{
    for (IWaveEvent* event : m_waveEvents)
    {
        event->OnWaveEnd();
    }
}
