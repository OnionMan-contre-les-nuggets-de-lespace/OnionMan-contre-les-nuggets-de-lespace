// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

namespace OnionMan:: Network
{
    /**
     *
     */
    //UCLASS()
    class ONIONMAN_UNREAL_API EncodingUtility
    {
    public:

        template<typename T>
        static void PutEncodedValueInBuffer(T value, TArray<uint8>& buffer, int& offset);

        template<typename T>
        static TArray<uint8> Encode(T value);

        template<typename T>
        static T Decode(TArray<uint8> bytes, int& offset, int size = -1);

        static void PutToBuffer(TArray<uint8>& toBuffer, TArray<uint8>& fromBuffer, int& offset);
        static void PutToBuffer(TArray<uint8>& toBuffer, const uint8* fromBuffer, int& offset, int fromBufferSize);


        template<typename T>
        static int GetSizeOf(T value = default);

        template<typename T>
        static bool HasFixedEncodedSize();

        static FString GetBytesAsString(TArray<uint8> bytes);
        static TArray<uint8> GetStringAsBytes(FString stringifiedBytes);
    };
}
