// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWaveEvent.h"

class Wave
{
private:
    TArray<IWaveEvent*> m_waveEvents;
public:
    Wave(/* args */);
    ~Wave();
};

Wave::Wave(/* args */)
{
}

Wave::~Wave()
{
}
