// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/Events/BaseWaveEvent.h"

UBaseWaveEvent::UBaseWaveEvent(/* args */)
{
    m_isFinished = false;
}

void UBaseWaveEvent::Load(AActor* levelAsset)
{
    m_isFinished = false;
    m_levelAsset = levelAsset;
}

void UBaseWaveEvent::Start()
{
}

void UBaseWaveEvent::Update(float deltaTime, float currentWaveTime)
{
}

void UBaseWaveEvent::OnWaveEnd()
{
}

void UBaseWaveEvent::EditorLoad(float timeSinceStart, AActor* levelAsset)
{
    if(m_isEditorLoaded)
    {
        return;
    }
    m_isEditorLoaded = true;
    m_levelAsset = levelAsset;
}

void UBaseWaveEvent::EditorUpdate(float newTimeSinceWaveStart)
{
    if(!m_isEditorLoaded)
    {
        return;
    }
}

void UBaseWaveEvent::EditorUnload()
{
    if(!m_isEditorLoaded)
    {
        return;
    }
    m_isEditorLoaded = false;
}

void UBaseWaveEvent::EditorSave()
{
    if(!m_isEditorLoaded)
    {
        return;
    }
}

void UBaseWaveEvent::Finish()
{
    m_isFinished = true;
    OnFinish();
}

void UBaseWaveEvent::OnFinish()
{
}