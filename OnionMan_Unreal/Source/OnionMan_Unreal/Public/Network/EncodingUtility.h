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
            return T{};
        }

        template<>
        static FString Decode<FString>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (size == -1)
            {
                LOG_ERROR("In order to decode a string, the argument 'size' must be set");
                return FString{};
           
            }
            if (offset + size <= bytes.Num()) 
            {
                FString decodedString = FString(size / sizeof(TCHAR), WCHAR_TO_TCHAR(bytes.GetData() + offset));
                offset += size;
                LOG_ERROR("Decoded Value : %s", *decodedString);
                return decodedString;
            }
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<FString>");
            return FString{};
        }

        template<>
        static bool Decode<bool>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                bool decodedValue = *((bool*)(bytes.GetData() + offset));
                offset += sizeof(bool);
                LOG_ERROR("Decoded Value : %s", decodedValue ? *FString("True") : *FString("False"));
                return decodedValue;
            }
            offset += sizeof(bool);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<bool>");
            return bool{};
        }

        template<>
        static TCHAR Decode<TCHAR>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                char decodedValue = *((TCHAR*)(bytes.GetData() + offset));
                offset += sizeof(TCHAR);
                return decodedValue;
            }
            offset += sizeof(TCHAR);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<TCHAR>");
            return TCHAR{};
        }

        template<>
        static double Decode<double>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                double decodedValue = *((double*)(bytes.GetData() + offset));
                offset += sizeof(double);
                LOG_ERROR("Decoded Value : %f", (double)decodedValue);
                return decodedValue;
            }
            offset += sizeof(double);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<double>");
            return double{};
        }

        template<>
        static float Decode<float>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                float decodedValue = *((float*)(bytes.GetData() + offset));
                offset += sizeof(float);
                LOG_ERROR("Decoded Value : %f", decodedValue);
                return decodedValue;
            }
            offset += sizeof(float);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<float>");
            return float{};
        }

        template<>
        static int Decode<int>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                int decodedValue = *((int*)(bytes.GetData() + offset));
                offset += sizeof(int);
                LOG_ERROR("Decoded Value : %i", decodedValue);
                return decodedValue;
            }
            offset += sizeof(int);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<int>");
            return int{};
        }

        template<>
        static int64 Decode<int64>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                int64 decodedValue = *((int64*)(bytes.GetData() + offset));
                offset += sizeof(int64);
                LOG_ERROR("Decoded Value : %i", (int)decodedValue);
                return decodedValue;
            }
            offset += sizeof(int64);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<int64>");
            return int64{};
        }

        template<>
        static int16 Decode<short>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                int16 decodedValue = *((int16*)(bytes.GetData() + offset));
                offset += sizeof(int16);
                LOG_ERROR("Decoded Value : %i", (int)decodedValue);
                return decodedValue;
            }
            offset += sizeof(int16);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<int16>");
            return int16{};
        }

        template<>
        static uint32 Decode<uint32>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                uint32 decodedValue = *((uint32*)(bytes.GetData() + offset));
                offset += sizeof(uint32);
                LOG_ERROR("Decoded Value : %i", (int)decodedValue);
                return decodedValue;
            }
            offset += sizeof(uint32);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<uint32>");
            return uint32{};
        }

        template<>
        static uint64 Decode<uint64>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                uint64 decodedValue = *((uint64*)(bytes.GetData() + offset));
                offset += sizeof(uint64);
                LOG_ERROR("Decoded Value : %i", (int)decodedValue);
                return decodedValue;
            }
            offset += sizeof(uint64);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<uint64>");
            return uint64{};
        }

        template<>
        static uint16 Decode<uint16>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                uint16 decodedValue = *((uint16*)(bytes.GetData() + offset));
                offset += sizeof(uint16);
                LOG_ERROR("Decoded Value : %i", (int)decodedValue);
                return decodedValue;
            }
            offset += sizeof(uint16);
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<uint16>");
            return uint16{};
        }

        template<>
        static FVector3f Decode<FVector3f>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                return FVector3f(
                    Decode<float>(bytes, offset),
                    Decode<float>(bytes, offset),
                    Decode<float>(bytes, offset));
            }
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<FVector3f>");
            return FVector3f{};
        }

        template<>
        static FIntVector Decode<FIntVector>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                return FIntVector(
                    Decode<int>(bytes, offset),
                    Decode<int>(bytes, offset),
                    Decode<int>(bytes, offset));
            }
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<FIntVector>");
            return FIntVector{};
        }

        template<>
        static FVector2f Decode<FVector2f>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                return FVector2f(
                    Decode<float>(bytes, offset),
                    Decode<float>(bytes, offset));
            }
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<FVector2f>");
            return FVector2f{};
        }

        template<>
        static FIntVector2 Decode<FIntVector2>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                return FIntVector2(
                    Decode<int>(bytes, offset),
                    Decode<int>(bytes, offset));
            }
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<FIntVector2>");
            return FIntVector2{};
        }

        template<>
        static FQuat4f Decode<FQuat4f>(TArray<uint8>& bytes, int& offset, int size)
        {
            if (offset + size <= bytes.Num())
            {
                return FQuat4f(
                    Decode<float>(bytes, offset),
                    Decode<float>(bytes, offset),
                    Decode<float>(bytes, offset),
                    Decode<float>(bytes, offset));
            }
            LOG_ERROR("Trying to read a value outside of byte buffer in Decode<FQuat4f>");
            return FQuat4f{};
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
