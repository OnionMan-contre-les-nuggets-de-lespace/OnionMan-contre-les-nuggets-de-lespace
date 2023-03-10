// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Wave.h"

UWave::UWave(/* args */)
{
    m_isFinished = false;
}

void UWave::Load()
{

    m_waveEvents.Sort(
        [&](UBaseWaveEvent& event1, UBaseWaveEvent& event2) 
        {
            return event1.GetTime() < event2.GetTime(); 
        });

    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->Load();
    }
}

void UWave::Update(float deltaTime, float currentWaveTime)
{
    // Starts the new events
    int eventsCount = m_waveEvents.Num();
    while (m_eventToStartIndex <= eventsCount && currentWaveTime >= m_waveEvents[m_eventToStartIndex]->GetTime())
    {
        TObjectPtr<UBaseWaveEvent> eventToStart = m_waveEvents[m_eventToStartIndex];
        m_eventsThatStarted.Add(eventToStart);

        eventToStart->Start();

        m_eventToStartIndex++;
    }

    // Updates all started evants
    bool allEventFinished = true;
    for (TObjectPtr<UBaseWaveEvent> event : m_eventsThatStarted)
    {
        if (event->IsFinished())
        {
            continue;
        }
        allEventFinished = false;
        event->Update(deltaTime, currentWaveTime);
    }

    // Checks wether the wave is finished by checking wether all events started and finished
    if (allEventFinished && m_eventsThatStarted.Num() == eventsCount)
    {
        m_isFinished = true;
    }

}

void UWave::FinishWave()
{
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->OnWaveEnd();
    }
}

void UWave::EditorLoad(float timeSinceWaveStart)
{
    if (m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->EditorLoad(timeSinceWaveStart);
    }
}

void UWave::EditorUpdate(float newtimeSinceWaveStart)
{
    if (!m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->EditorUpdate(newtimeSinceWaveStart);
    }
}

void UWave::EditorUnload()
{
    if (!m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->EditorUnload();
    }
}

void UWave::EditorSave()
{
    if (!m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->EditorSave();
    }
}
