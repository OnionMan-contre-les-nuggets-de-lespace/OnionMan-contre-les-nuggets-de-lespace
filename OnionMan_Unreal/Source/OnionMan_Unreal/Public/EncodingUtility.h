// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace OnionMan:: Network
{
    /**
     *
     */
    UCLASS()
        class ONIONMAN_UNREAL_API EncodingUtility
    {
    public:
        EncodingUtility();
        ~EncodingUtility();

        template<typename T>
        static TArray<uint8> Encode(T value);

        template<typename T>
        static T Decode(TArray<uint8> bytes, int& offset, int size = -1);


        FString GetBytesAsString(TArray<uint8> bytes);
        TArray<uint8> GetStringAsBytes(FString stringifiedBytes);
    };
}
