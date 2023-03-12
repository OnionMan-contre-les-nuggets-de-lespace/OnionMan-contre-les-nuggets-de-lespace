// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogUtils.h"

namespace OnionMan:: Network
{
    /**
     *
     */
    // UCLASS()
    class ONIONMAN_UNREAL_API EncodingUtility
    {
    public:

#pragma region PutEncodedValueInBuffer 

        template<typename T>
        static void PutEncodedValueInBuffer(T value, TArray<uint8>& buffer, int& offset)
        {
        }

        template<>
        static void PutEncodedValueInBuffer<FString>(FString value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (const uint8*)TCHAR_TO_WCHAR(*value), offset, value.Len() * sizeof(TCHAR));
        }

        template<>
        static void PutEncodedValueInBuffer<bool>(bool value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(bool));
        }

        template<>
        static void PutEncodedValueInBuffer<TCHAR>(TCHAR value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(TCHAR));
        }

        template<>
        static void PutEncodedValueInBuffer<double>(double value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(double));
        }

        template<>
        static void PutEncodedValueInBuffer<float>(float value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(float));
        }

        template<>
        static void PutEncodedValueInBuffer<int>(int value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(int));
        }

        template<>
        static void PutEncodedValueInBuffer<long>(long value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(long));
        }

        template<>
        static void PutEncodedValueInBuffer<short>(short value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(short));
        }

        template<>
        static void PutEncodedValueInBuffer<uint32>(uint32 value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint32));
        }

        template<>
        static void PutEncodedValueInBuffer<uint64>(uint64 value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint64));
        }

        template<>
        static void PutEncodedValueInBuffer<uint16>(uint16 value, TArray<uint8>& buffer, int& offset)
        {
            PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint16));
        }

        template<>
        static void PutEncodedValueInBuffer<FVector3f>(FVector3f value, TArray<uint8>& buffer, int& offset)
        {
            PutEncodedValueInBuffer(value.X, buffer, offset);
            PutEncodedValueInBuffer(value.Y, buffer, offset);
            PutEncodedValueInBuffer(value.Z, buffer, offset);
        }

        template<>
        static void PutEncodedValueInBuffer<FIntVector>(FIntVector value, TArray<uint8>& buffer, int& offset)
        {
            PutEncodedValueInBuffer(value.X, buffer, offset);
            PutEncodedValueInBuffer(value.Y, buffer, offset);
            PutEncodedValueInBuffer(value.Z, buffer, offset);
        }

        template<>
        static void PutEncodedValueInBuffer<FVector2f>(FVector2f value, TArray<uint8>& buffer, int& offset)
        {
            PutEncodedValueInBuffer(value.X, buffer, offset);
            PutEncodedValueInBuffer(value.Y, buffer, offset);
        }

        template<>
        static void PutEncodedValueInBuffer<FIntVector2>(FIntVector2 value, TArray<uint8>& buffer, int& offset)
        {
            PutEncodedValueInBuffer(value.X, buffer, offset);
            PutEncodedValueInBuffer(value.Y, buffer, offset);
        }

        template<>
        static void PutEncodedValueInBuffer<FQuat4f>(FQuat4f value, TArray<uint8>& buffer, int& offset)
        {
            PutEncodedValueInBuffer(value.X, buffer, offset);
            PutEncodedValueInBuffer(value.Y, buffer, offset);
            PutEncodedValueInBuffer(value.Z, buffer, offset);
            PutEncodedValueInBuffer(value.W, buffer, offset);
        }

#pragma endregion
    
#pragma region Decode
        template <typename T>
        static T Decode(TArray<uint8>& bytes, int& offset, int size = -1)
        {
            LOG_ERROR("The type %s cannot be decoded yet", internal::GetTypeNameHelper<T>::GetTypeName());
            return NULL;
        }

        template<>
        static FString Decode<FString>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (size == -1)
            {
                LOG_ERROR("In order to decode a string, the argument 'size' must be set");
                return FString{};
           
            }
            FString decodedString = FString(WCHAR_TO_TCHAR(bytes.GetData() + offset));
            offset += size;
            LOG_ERROR("Decoded Value : %s", *decodedString)
            return decodedString;
        }

        template<>
        static bool Decode<bool>(TArray<uint8>& bytes, int& offset, int size)
        {
            bool decodedValue = *((bool*)(bytes.GetData() + offset));
            offset += sizeof(bool);
            LOG_ERROR("Decoded Value : %b", decodedValue)
            return decodedValue;
        }

        template<>
        static char Decode<char>(TArray<uint8>& bytes, int& offset, int size)
        {
            char decodedValue = *((char*)(bytes.GetData() + offset));
            offset += sizeof(char);
            return decodedValue;
        }

        template<>
        static double Decode<double>(TArray<uint8>& bytes, int& offset, int size)
        {
            double decodedValue = *((double*)(bytes.GetData() + offset));
            offset += sizeof(double);
            return decodedValue;
        }

        template<>
        static float Decode<float>(TArray<uint8>& bytes, int& offset, int size)
        {
            float decodedValue = *((float*)(bytes.GetData() + offset));
            offset += sizeof(float);
            LOG_ERROR("Decoded Value : %f", decodedValue)
            return decodedValue;
        }

        template<>
        static int Decode<int>(TArray<uint8>& bytes, int& offset, int size)
        {
            int decodedValue = *((int*)(bytes.GetData() + offset));
            offset += sizeof(int);
            LOG_ERROR("Decoded Value : %i", decodedValue)
            return decodedValue;
        }

        template<>
        static long Decode<long>(TArray<uint8>& bytes, int& offset, int size)
        {
            long decodedValue = *((long*)(bytes.GetData() + offset));
            offset += sizeof(long);
            return decodedValue;
        }

        template<>
        static short Decode<short>(TArray<uint8>& bytes, int& offset, int size)
        {
            short decodedValue = *((short*)(bytes.GetData() + offset));
            offset += sizeof(short);
            return decodedValue;
        }

        template<>
        static uint32 Decode<uint32>(TArray<uint8>& bytes, int& offset, int size)
        {
            uint32 decodedValue = *((uint32*)(bytes.GetData() + offset));
            offset += sizeof(uint32);
            return decodedValue;
        }

        template<>
        static uint64 Decode<uint64>(TArray<uint8>& bytes, int& offset, int size)
        {
            uint64 decodedValue = *((uint64*)(bytes.GetData() + offset));
            offset += sizeof(uint64);
            return decodedValue;
        }

        template<>
        static uint16 Decode<uint16>(TArray<uint8>& bytes, int& offset, int size)
        {
            uint16 decodedValue = *((uint16*)(bytes.GetData() + offset));
            offset += sizeof(uint16);
            return decodedValue;
        }

        template<>
        static FVector3f Decode<FVector3f>(TArray<uint8>& bytes, int& offset, int size)
        {
            return FVector3f(
                Decode<float>(bytes, offset),
                Decode<float>(bytes, offset),
                Decode<float>(bytes, offset));
        }

        template<>
        static FIntVector Decode<FIntVector>(TArray<uint8>& bytes, int& offset, int size)
        {
            return FIntVector(
                Decode<int>(bytes, offset),
                Decode<int>(bytes, offset),
                Decode<int>(bytes, offset));
        }

        template<>
        static FVector2f Decode<FVector2f>(TArray<uint8>& bytes, int& offset, int size)
        {
            return FVector2f(
                Decode<float>(bytes, offset),
                Decode<float>(bytes, offset));
        }

        template<>
        static FIntVector2 Decode<FIntVector2>(TArray<uint8>& bytes, int& offset, int size)
        {
            return FIntVector2(
                Decode<int>(bytes, offset),
                Decode<int>(bytes, offset));
        }

        template<>
        static FQuat4f Decode<FQuat4f>(TArray<uint8>& bytes, int& offset, int size)
        {
            return FQuat4f(
                Decode<float>(bytes, offset),
                Decode<float>(bytes, offset),
                Decode<float>(bytes, offset),
                Decode<float>(bytes, offset));
        }

#pragma endregion

        static void PutToBuffer(TArray<uint8>& toBuffer, TArray<uint8>& fromBuffer, int& offset);
        static void PutToBuffer(TArray<uint8>& toBuffer, const uint8* fromBuffer, int& offset, int fromBufferSize);

#pragma region GetSizeOf
        template<typename T>
        static int GetSizeOf(T* value = nullptr)
        {
            return sizeof(T);
        }

        template<>
        static int GetSizeOf<FString>(FString* value)
        {
            return value->Len() * sizeof(TCHAR);
        }

        template<>
        static int GetSizeOf<FVector3f>(FVector3f* value)
        {
            return 3 * sizeof(float);
        }

        template<>
        static int GetSizeOf<FIntVector>(FIntVector* value)
        {
            return 3 * sizeof(int);
        }

        template<>
        static int GetSizeOf<FVector2f>(FVector2f* value)
        {
            return 2 * sizeof(float);
        }

        template<>
        static int GetSizeOf<FIntVector2>(FIntVector2* value)
        {
            return 2 * sizeof(int);
        }

        template<>
        static int GetSizeOf<FQuat4f>(FQuat4f* value)
        {
            return 4 * sizeof(float);
        }

#pragma endregion

#pragma region HasFixedEncodedSize
        template<typename T>
        static bool HasFixedEncodedSize()
        {
            return true;
        }

        template<>
        static bool HasFixedEncodedSize<FString>()
        {
            return false;
        }
#pragma endregion

        static FString GetBytesAsString(const TArray<uint8>& bytes);
        static void GetStringAsBytes(FString stringifiedBytes, TArray<uint8>& bytes);
    };
}
