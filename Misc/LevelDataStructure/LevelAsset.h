// Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"
// #include "Wave.h"

class ULevelAsset
{
private:
    float m_currentTime = 0.0f;

    TArray<Wave*> m_waves;

    int m_currentWaveIndex = 0;
    Wave* m_currentWave;

public:
    ULevelAsset(/* args */);
    ~ULevelAsset();

    inline float CurrentTime()
    {
        return m_currentTime;
    }

    void Load();

    void Update(float deltaTime);
};

ULevelAsset::ULevelAsset(/* args */)
{
}

ULevelAsset::~ULevelAsset()
{
}

void ULevelAsset::Load()
{
}

void ULevelAsset::Update(float deltaTime)
{
    m_currentTime += deltaTime;
    m_currentWave->Update(deltaTime);

    if (m_currentWave->IsFinished())
    {
        m_currentWave->FinishWave();

        m_currentWaveIndex++;
        m_currentWave = m_waves[m_currentWaveIndex];

        m_currentWave->Load(this);
    }
}
