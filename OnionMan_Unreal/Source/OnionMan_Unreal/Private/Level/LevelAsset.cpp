// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelAsset.h"



ALevelAsset::ALevelAsset(/* args */)
{
}

void ALevelAsset::Load()
{
}

void ALevelAsset::Update(float deltaTime)
{
    m_currentLevelTime += deltaTime;
    m_currentWaveTime += deltaTime;

    m_currentWave->Update(deltaTime, m_currentWaveTime);

    if (m_currentWave->IsFinished())
    {
        m_currentWave->FinishWave();

        m_currentWaveIndex++;
        m_currentWave = m_waves[m_currentWaveIndex];

        m_currentWaveTime = 0.0f;
        m_currentWave->Load();
    }
}