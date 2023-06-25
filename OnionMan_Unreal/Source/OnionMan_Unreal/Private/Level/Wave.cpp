// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Wave.h"

#include "LogUtils.h"

UWave::UWave(/* args */)
{
    m_isFinished = false;
}

void UWave::Load(AActor* levelAsset)
{
    m_eventsCount = m_waveEvents.Num(); 
    m_eventToStartIndex = 0;
    m_waveEvents.Sort(
        [&](UBaseWaveEvent& event1, UBaseWaveEvent& event2) 
        {
            return event1.GetTime() < event2.GetTime(); 
        });

    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        if (event)
        {
            event->Load(levelAsset);
        }
    }
}

void UWave::Update(float deltaTime, float currentWaveTime)
{
    // Starts the new events
    while (m_eventToStartIndex < m_eventsCount 
        && m_waveEvents[m_eventToStartIndex] != nullptr 
        && currentWaveTime >= m_waveEvents[m_eventToStartIndex]->GetTime())
    {
        TObjectPtr<UBaseWaveEvent> eventToStart = m_waveEvents[m_eventToStartIndex];
        if (eventToStart)
        {
            m_eventsThatStarted.Add(eventToStart);

            eventToStart->Start();
        }
        m_eventToStartIndex++;
    }
    LOG_WARNING("WaveUpdate")
    // Updates all started evants
    bool allEventFinished = true;
    for (TObjectPtr<UBaseWaveEvent> event : m_eventsThatStarted)
    {
        if (event)
        {
            if (event->IsFinished())
            {
                continue;
            }
            allEventFinished = false;
            event->Update(deltaTime, currentWaveTime);
        }
    }

    // Checks whether the wave is finished by checking whether all events started and finished
    if (allEventFinished && m_eventsThatStarted.Num() == m_eventsCount)
    {
        LOG_ERROR("WaveFinished");
        m_isFinished = true;
    }

}

void UWave::FinishWave()
{
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        if (event)
        {
            event->OnWaveEnd();
        }
    }
}

#if WITH_EDITOR
void UWave::EditorLoad(float timeSinceWaveStart, AActor* levelAsset)
{
    if (m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->EditorLoad(timeSinceWaveStart, levelAsset);
        m_isEditorLoaded = true;
    }
}

void UWave::EditorUpdate(float newTimeSinceWaveStart)
{
    if (!m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        event->EditorUpdate(newTimeSinceWaveStart);
    }
}

void UWave::EditorUnload()
{
    LOG_ERROR("UWave::EditorUnload()")
    if (!m_isEditorLoaded)
    {
        LOG_ERROR("Wave Not loaded")
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        if (event)
        {
            LOG_ERROR("UnloadingEvent")
            event->EditorUnload();
        }
    }
    m_isEditorLoaded = false;
}

void UWave::EditorSave()
{
    if (!m_isEditorLoaded)
    {
        return;
    }
    for (TObjectPtr<UBaseWaveEvent> event : m_waveEvents)
    {
        if (event)
        {
            event->EditorSave();
        }
    }
}
#endif
