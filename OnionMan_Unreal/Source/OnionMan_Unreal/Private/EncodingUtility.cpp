#include "EncodingUtility.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Core/Public/Math/Quat.h"
#include "Runtime/Core/Public/Math/IntVector.h"

namespace OnionMan::Network 
{
#pragma region PutEncodedValueInBuffer
    /*
    template<typename T>
    void EncodingUtility::PutEncodedValueInBuffer(T value, TArray<uint8>& buffer, int& offset)
    {
    }

    template<> 
    static void EncodingUtility::PutEncodedValueInBuffer<FString>(FString value, TArray<uint8>&buffer, int& offset)
    {
        PutToBuffer(buffer, (const uint8*)TCHAR_TO_UTF8(*value), offset, value.Len());
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<bool>(bool value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(bool));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<char>(char value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(char));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<double>(double value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(double));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<float>(float value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(float));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<int>(int value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(int));
    }

    template<> 
    static void EncodingUtility::PutEncodedValueInBuffer<long>(long value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(long));
    }

    template<> 
    static void EncodingUtility::PutEncodedValueInBuffer<short>(short value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(short));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<uint32>(uint32 value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint32));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<uint64>(uint64 value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint64));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<uint16>(uint16 value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint16));
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<FVector3f>(FVector3f value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
        PutEncodedValueInBuffer(value.Z, buffer, offset);
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<FIntVector>(FIntVector value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
        PutEncodedValueInBuffer(value.Z, buffer, offset);
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<FVector2f>(FVector2f value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<FIntVector2>(FIntVector2 value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
    }

    template<>
    static void EncodingUtility::PutEncodedValueInBuffer<FQuat4f>(FQuat4f value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
        PutEncodedValueInBuffer(value.Z, buffer, offset);
        PutEncodedValueInBuffer(value.W, buffer, offset);
    }
    */
#pragma endregion

#pragma region Encode
    /*
    template <typename T> 
    static void EncodingUtility::Encode(T value, TArray<uint8>& encodedValue)
    {
        throw "The type " << T << "cannot be encoded yet";
    }

    template<>
    static void EncodingUtility::Encode<FString>(FString value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (const uint8*)TCHAR_TO_UTF8(*value), value.Len() };
    }

    template<> 
    static void EncodingUtility::Encode<bool>(bool value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(bool) };
    }

    template<> 
    static void EncodingUtility::Encode<char>(char value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(char) };
    }

    template<> 
    static void EncodingUtility::Encode<double>(double value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(double) };
    }

    template<> 
    static void EncodingUtility::Encode<float>(float value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(float) };
    }

    template<> 
    static void EncodingUtility::Encode<int>(int value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(int) };
    }

    template<>
    static void EncodingUtility::Encode<long>(long value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(long) };
    }

    template<>
    static void EncodingUtility::Encode<short>(short value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(short) };
    }

    template<>
    static void EncodingUtility::Encode<uint32>(uint32 value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(uint32) };
    }

    template<>
    static void EncodingUtility::Encode<uint64>(uint64 value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(uint64) };
    }

    template<>
    static void EncodingUtility::Encode<uint16>(uint16 value, TArray<uint8>& encodedValue)
    {
        encodedValue = TArray<uint8>{ (uint8*)&value, sizeof(uint16) };
    }

    template<>
    static void EncodingUtility::Encode<FVector3f>(FVector3f value, TArray<uint8>& encodedValue)
    {
        encodedValue.Empty();
        encodedValue.Reserve(3 * sizeof(float));

        TArray<uint8> encodedElement{};

        Encode(value.X, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Y, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Z, encodedElement);
        encodedValue.Append(encodedElement);
    }

    template<>
    static void EncodingUtility::Encode<FIntVector>(FIntVector value, TArray<uint8>& encodedValue)
    {
        encodedValue.Empty();
        encodedValue.Reserve(3 * sizeof(int));

        TArray<uint8> encodedElement{};

        Encode(value.X, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Y, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Z, encodedElement);
        encodedValue.Append(encodedElement);
    }

    template<>
    static void EncodingUtility::Encode<FVector2f>(FVector2f value, TArray<uint8>& encodedValue)
    {
        encodedValue.Empty();
        encodedValue.Reserve(2 * sizeof(float));

        TArray<uint8> encodedElement{};

        Encode(value.X, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Y, encodedElement);
        encodedValue.Append(encodedElement);
    }

    template<>
    static void EncodingUtility::Encode<FIntVector2>(FIntVector2 value, TArray<uint8>& encodedValue)
    {
        encodedValue.Empty();
        encodedValue.Reserve(2 * sizeof(int));

        TArray<uint8> encodedElement{};

        Encode(value.X, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Y, encodedElement);
        encodedValue.Append(encodedElement);
    }

    template<>
    static void EncodingUtility::Encode<FQuat4f>(FQuat4f value, TArray<uint8>& encodedValue)
    {
        encodedValue.Empty();
        encodedValue.Reserve(4 * sizeof(float));

        TArray<uint8> encodedElement{};

        Encode(value.X, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Y, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.Z, encodedElement);
        encodedValue.Append(encodedElement);

        Encode(value.W, encodedElement);
        encodedValue.Append(encodedElement);
    }
    */
#pragma endregion

#pragma region Decode
/*
    template <typename T>
    static T EncodingUtility::Decode(TArray<uint8> bytes, int& offset, int size)
    {
        throw "The type " << T << "cannot be decoded yet";
    }

    template<>
    static FString EncodingUtility::Decode<FString>(TArray<uint8> bytes, int& offset, int size)
    {
        if (size == -1)
        {
            throw "In order to decode a string, the argument 'size' must be set";
        }
        FString decodedString = FString(UTF8_TO_TCHAR(bytes.GetData() + offset));
        offset += size;
        return decodedString;
    }

    template<>
    static bool EncodingUtility::Decode<bool>(TArray<uint8> bytes, int& offset, int size)
    {
        bool decodedValue = *((bool*)(bytes.GetData() + offset));
        offset += sizeof(bool);
        return decodedValue;
    }

    template<>
    static char EncodingUtility::Decode<char>(TArray<uint8> bytes, int& offset, int size)
    {
        char decodedValue = *((char*)(bytes.GetData() + offset));
        offset += sizeof(char);
        return decodedValue;
    }

    template<>
    static double EncodingUtility::Decode<double>(TArray<uint8> bytes, int& offset, int size)
    {
        double decodedValue = *((double*)(bytes.GetData() + offset));
        offset += sizeof(double);
        return decodedValue;
    }

    template<>
    static float EncodingUtility::Decode<float>(TArray<uint8> bytes, int& offset, int size)
    {
        float decodedValue = *((float*)(bytes.GetData() + offset));
        offset += sizeof(float);
        return decodedValue;
    }

    template<>
    static int EncodingUtility::Decode<int>(TArray<uint8> bytes, int& offset, int size)
    {
        int decodedValue = *((int*)(bytes.GetData() + offset));
        offset += sizeof(int);
        return decodedValue;
    }

    template<>
    static long EncodingUtility::Decode<long>(TArray<uint8> bytes, int& offset, int size)
    {
        long decodedValue = *((long*)(bytes.GetData() + offset));
        offset += sizeof(long);
        return decodedValue;
    }

    template<>
    static short EncodingUtility::Decode<short>(TArray<uint8> bytes, int& offset, int size)
    {
        short decodedValue = *((short*)(bytes.GetData() + offset));
        offset += sizeof(short);
        return decodedValue;
    }

    template<>
    static uint32 EncodingUtility::Decode<uint32>(TArray<uint8> bytes, int& offset, int size)
    {
        uint32 decodedValue = *((uint32*)(bytes.GetData() + offset));
        offset += sizeof(uint32);
        return decodedValue;
    }

    template<>
    static uint64 EncodingUtility::Decode<uint64>(TArray<uint8> bytes, int& offset, int size)
    {
        uint64 decodedValue = *((uint64*)(bytes.GetData() + offset));
        offset += sizeof(uint64);
        return decodedValue;
    }

    template<>
    static uint16 EncodingUtility::Decode<uint16>(TArray<uint8> bytes, int& offset, int size)
    {
        uint16 decodedValue = *((uint16*)(bytes.GetData() + offset));
        offset += sizeof(uint16);
        return decodedValue;
    }

    template<>
    static FVector3f EncodingUtility::Decode<FVector3f>(TArray<uint8> bytes, int& offset, int size)
    {
        return FVector3f(
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset));
    }

    template<>
    static FIntVector EncodingUtility::Decode<FIntVector>(TArray<uint8> bytes, int& offset, int size)
    {
        return FIntVector(
            Decode<int>(bytes, offset),
            Decode<int>(bytes, offset),
            Decode<int>(bytes, offset));
    }

    template<>
    static FVector2f EncodingUtility::Decode<FVector2f>(TArray<uint8> bytes, int& offset, int size)
    {
        return FVector2f(
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset));
    }

    template<>
    static FIntVector2 EncodingUtility::Decode<FIntVector2>(TArray<uint8> bytes, int& offset, int size)
    {
        return FIntVector2(
            Decode<int>(bytes, offset),
            Decode<int>(bytes, offset));
    }

    template<>
    static FQuat4f EncodingUtility::Decode<FQuat4f>(TArray<uint8> bytes, int& offset, int size)
    {
        return FQuat4f(
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset));
    }
    */
#pragma endregion

#pragma region PutToBuffer
    void EncodingUtility::PutToBuffer(TArray<uint8>& toBuffer, TArray<uint8>& fromBuffer, int& offset)
    {
        for (int i{ 0 }; i < fromBuffer.Num(); i++, offset++)
        {
            toBuffer[offset] = fromBuffer[i];
        }
    }

    void EncodingUtility::PutToBuffer(TArray<uint8>& toBuffer, const uint8* fromBuffer, int& offset, int fromBufferSize)
    {
        for (int i{ 0 }; i < fromBufferSize; i++, offset++)
        {
            toBuffer[offset] = fromBuffer[i];
        }
    }
#pragma endregion
/*
#pragma region GetSizeOf

    template<typename T>
    static int EncodingUtility::GetSizeOf(T* value)
    {
        return sizeof(T);
    }

    template<>
    static int EncodingUtility::GetSizeOf<FString>(FString* value)
    {
        TArray<uint8> encodedString;
        int offset = 0;
        PutEncodedValueInBuffer(*value, encodedString, offset);
        return encodedString.Num();
    }

    template<>
    static int EncodingUtility::GetSizeOf<FVector3f>(FVector3f* value)
    {
        return 3 * sizeof(float);
    }

    template<>
    static int EncodingUtility::GetSizeOf<FIntVector>(FIntVector* value)
    {
        return 3 * sizeof(int);
    }

    template<>
    static int EncodingUtility::GetSizeOf<FVector2f>(FVector2f* value)
    {
        return 2 * sizeof(float);
    }

    template<>
    static int EncodingUtility::GetSizeOf<FIntVector2>(FIntVector2* value)
    {
        return 2 * sizeof(int);
    }

    template<>
    static int EncodingUtility::GetSizeOf<FQuat4f>(FQuat4f* value)
    {
        return 4 * sizeof(float);
    }

#pragma endregion
*/
/*
#pragma region HasFixedEncodedSize
    template<typename T>
    static bool EncodingUtility::HasFixedEncodedSize()
    {
        return true;
    }

    template<>
    static bool EncodingUtility::HasFixedEncodedSize<FString>()
    {
        return false;
    }
    */
#pragma endregion

#pragma region Debug
    FString EncodingUtility::GetBytesAsString(const TArray<uint8>& bytes)
    {
        FString returnValue;
        int byteCount = bytes.Num();
        for (int i = 0; i < byteCount; i++)
        {
            returnValue += FString::FromInt(bytes[i]) + (i < byteCount - 1 ? "|" : "");
        }
        return returnValue;
    }

    void EncodingUtility::GetStringAsBytes(FString stringifiedBytes, TArray<uint8>& bytes)
    {
        TArray<FString> splittedString;
        stringifiedBytes.ParseIntoArray(splittedString, TEXT("|"), true);

        bytes.Empty();
        bytes.SetNumUninitialized(splittedString.Num());
        for (int i = 0; i < splittedString.Num(); i++)
        {
            bytes[i] = FCString::Atoi(*splittedString[i]);
        }
    }
#pragma endregion
}