// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/BaseWaveEvent.h"

UBaseWaveEvent::UBaseWaveEvent(/* args */)
{
    m_isFinished = false;
}

void UBaseWaveEvent::Load()
{
    m_isFinished = false;
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

void UBaseWaveEvent::EditorLoad(float time)
{
}

void UBaseWaveEvent::EditorUnload()
{
}

void UBaseWaveEvent::Finish()
{
    m_isFinished = true;
    OnFinish();
}

void UBaseWaveEvent::OnFinish()
{
}