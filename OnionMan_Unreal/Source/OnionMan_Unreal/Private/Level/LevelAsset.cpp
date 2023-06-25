// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelAsset.h"



ALevelAsset::ALevelAsset(/* args */)
{
}

void ALevelAsset::Load()
{
    
#if WITH_EDITOR
    for (UWave* wave : m_waves) 
    {
        wave->EditorUnload();
    }
#endif

    m_currentWaveIndex = 0;
    if (m_waves.Num() > 0)
    {
        m_currentWave = m_waves[m_currentWaveIndex];
        m_currentWave->Load(this);
    }
    else
    {
        m_currentWave = nullptr;
    }
}

bool ALevelAsset::Update(float deltaTime)
{
    if (m_currentWave != nullptr)
    {
        m_currentLevelTime += deltaTime;
        m_currentWaveTime += deltaTime;

        m_currentWave->Update(deltaTime, m_currentWaveTime);

        if (m_currentWave->IsFinished())
        {
            m_currentWave->FinishWave();

            m_currentWaveIndex++;
            if (m_currentWaveIndex < m_waves.Num())
            {
                m_currentWave = m_waves[m_currentWaveIndex];

                m_currentWaveTime = 0.0f;
                m_currentWave->Load(this);
            }
            else
            {
                m_currentWave = nullptr;
                LOG_ERROR("LEVEL FINISHED")
                return true;
            }
        }
    }
    return false;
}

#if WITH_EDITOR
void ALevelAsset::EditorLoad()
{
    if (0 <= m_waveToLoad && m_waveToLoad < m_waves.Num())
    {
        m_waves[m_waveToLoad]->EditorLoad(m_updateTime, this);
        m_loadedWave = m_waveToLoad;
    }
    else
    {
        LOG_ERROR("Could not load the wave %i", m_waveToLoad);
    }
}

void ALevelAsset::EditorUpdate()
{
    if (0 <= m_loadedWave && m_loadedWave < m_waves.Num())
    {
        m_waves[m_loadedWave]->EditorUpdate(m_updateTime);
    }
    else
    {
        LOG_ERROR("Could not update the wave %i", m_waveToLoad);
    }
}

void ALevelAsset::EditorUnload()
{
    if (0 <= m_loadedWave && m_loadedWave < m_waves.Num())
    {
        LOG_ERROR("Unloading Wave %i", m_waveToLoad)
        m_waves[m_loadedWave]->EditorUnload();
        m_loadedWave = -1;
    }
    else
    {
        LOG_ERROR("Could not unload the wave %i", m_waveToLoad)
    }
}
#endif