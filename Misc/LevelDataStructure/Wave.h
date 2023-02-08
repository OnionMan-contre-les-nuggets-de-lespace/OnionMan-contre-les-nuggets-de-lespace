// Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"
#include "IWaveEvent.h"
#include "LevelAsset.h"

class Wave
{
private:
    TArray<IWaveEvent*> m_waveEvents;

    TArray<IWaveEvent*> m_eventsThatStarted;

    ULevelAsset* m_levelAsset;

    bool m_isFinished = false;
    int m_eventToStartIndex = 0;

public:
    Wave(/* args */);
    ~Wave();

    inline bool IsFinished()
    {
        return m_isFinished;
    }

    void Load(ULevelAsset* level);
    void Update(float deltaTime);
    void FinishWave();

    // Editor
    void EditorLoad(float time);
    void EditorUnload();
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

    m_waveEvents.Sort([](IWaveEvent* event1, IWaveEvent* event2){return event1->GetTime() < event2->GetTime();});

    for (IWaveEvent* event : m_waveEvents)
    {
        event->Load();
    }
}

void Wave::Update(float deltaTime)
{
    // Starts the new events
    float currentTime = m_levelAsset->CurrentTime();
    int eventsCount = m_waveEvents.Num();
    while (m_eventToStartIndex <= eventsCount && currentTime >= m_waveEvents[m_eventToStartIndex]->GetTime())
    {
        IWaveEvent* eventToStart = m_waveEvents[m_eventToStartIndex];
        m_eventsThatStarted.Add(eventToStart);

        eventToStart->Start();

        m_eventToStartIndex++;
    }

    // Updates all started evants
    bool allEventFinished = true;
    for (IWaveEvent* event : m_eventsThatStarted)
    {
        if (event->IsFinished())
        {
            continue;
        }
        allEventFinished = false;
        event->Update(deltaTime);
    }

    // Checks wether the wave is finished by checking wether all events started and finished
    if (allEventFinished && m_eventsThatStarted.Num() == m_waveEvents.Num()) 
    {
        m_isFinished = true;
    }
    
}

void Wave::FinishWave()
{
    for (IWaveEvent* event : m_waveEvents)
    {
        event->OnWaveEnd();
    }
}

void Wave::EditorLoad(float time)
{
    for (IWaveEvent* event : m_waveEvents)
    {
        event->EditorLoad(time);
    }
}

void Wave::EditorUnload()
{
    for (IWaveEvent* event : m_waveEvents)
    {
        event->EditorUnload();
    }
}
