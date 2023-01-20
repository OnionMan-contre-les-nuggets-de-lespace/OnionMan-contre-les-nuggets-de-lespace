#include "EncodingUtility.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Core/Public/Math/Quat.h"
#include "Runtime/Core/Public/Math/IntVector.h"

namespace OnionMan::Network 
{
#pragma region PutEncodedValueInBuffer

    template<typename T>
    void EncodingUtility::PutEncodedValueInBuffer(T value, TArray<uint8>& buffer, int& offset)
    {
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<FString>(FString value, TArray<uint8>&buffer, int& offset)
    {
        PutToBuffer(buffer, (const uint8*)TCHAR_TO_UTF8(*value), offset, value.Len());
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<bool>(bool value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(bool));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<char>(char value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(char));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<double>(double value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(double));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<float>(float value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(float));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<int>(int value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(int));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<long>(long value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(long));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<short>(short value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(short));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<uint32>(uint32 value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint32));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<uint64>(uint64 value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint64));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<uint16>(uint16 value, TArray<uint8>& buffer, int& offset)
    {
        PutToBuffer(buffer, (uint8*)&value, offset, sizeof(uint16));
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<FVector3f>(FVector3f value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
        PutEncodedValueInBuffer(value.Z, buffer, offset);
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<FIntVector>(FIntVector value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
        PutEncodedValueInBuffer(value.Z, buffer, offset);
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<FVector2f>(FVector2f value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<FIntVector2>(FIntVector2 value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
    }

    template<>
    void EncodingUtility::PutEncodedValueInBuffer<FQuat4f>(FQuat4f value, TArray<uint8>& buffer, int& offset)
    {
        PutEncodedValueInBuffer(value.X, buffer, offset);
        PutEncodedValueInBuffer(value.Y, buffer, offset);
        PutEncodedValueInBuffer(value.Z, buffer, offset);
        PutEncodedValueInBuffer(value.W, buffer, offset);
    }

#pragma endregion

#pragma region Encode
    template <typename T> TArray<uint8> EncodingUtility::Encode(T value)
    {
        throw "The type " << T << "cannot be encoded yet";
    }

    template<> TArray<uint8> EncodingUtility::Encode<FString>(FString value)
    {
        return TArray<uint8>{ (const uint8*)TCHAR_TO_UTF8(*value), value.Len() };
    }

    template<> TArray<uint8> EncodingUtility::Encode<bool>(bool value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(bool) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<char>(char value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(char) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<double>(double value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(double) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<float>(float value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(float) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<int>(int value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(int) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<long>(long value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(long) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<short>(short value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(short) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<uint32>(uint32 value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(uint32) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<uint64>(uint64 value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(uint64) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<uint16>(uint16 value)
    {
        return TArray<uint8>{ (uint8*)&value, sizeof(uint16) };
    }

    template<> TArray<uint8> EncodingUtility::Encode<FVector3f>(FVector3f value)
    {
        TArray<uint8> encodedQuat{};
        encodedQuat.Reserve(3 * sizeof(float));
        encodedQuat.Append(Encode(value.X));
        encodedQuat.Append(Encode(value.Y));
        encodedQuat.Append(Encode(value.Z));
        return encodedQuat;
    }

    template<> TArray<uint8> EncodingUtility::Encode<FIntVector>(FIntVector value)
    {
        TArray<uint8> encodedQuat{};
        encodedQuat.Reserve(3 * sizeof(int));
        encodedQuat.Append(Encode(value.X));
        encodedQuat.Append(Encode(value.Y));
        encodedQuat.Append(Encode(value.Z));
        return encodedQuat;
    }

    template<> TArray<uint8> EncodingUtility::Encode<FVector2f>(FVector2f value)
    {
        TArray<uint8> encodedQuat{};
        encodedQuat.Reserve(2 * sizeof(float));
        encodedQuat.Append(Encode(value.X));
        encodedQuat.Append(Encode(value.Y));
        return encodedQuat;
    }

    template<> TArray<uint8> EncodingUtility::Encode<FIntVector2>(FIntVector2 value)
    {
        TArray<uint8> encodedQuat{};
        encodedQuat.Reserve(2 * sizeof(int));
        encodedQuat.Append(Encode(value.X));
        encodedQuat.Append(Encode(value.Y));
        return encodedQuat;
    }

    template<> TArray<uint8> EncodingUtility::Encode<FQuat4f>(FQuat4f value)
    {
        TArray<uint8> encodedQuat{};
        encodedQuat.Reserve(4 * sizeof(float));
        encodedQuat.Append(Encode(value.X));
        encodedQuat.Append(Encode(value.Y));
        encodedQuat.Append(Encode(value.Z));
        encodedQuat.Append(Encode(value.W));
        return encodedQuat;
    }

#pragma endregion

#pragma region Decode
    template <typename T> T EncodingUtility::Decode(TArray<uint8> bytes, int& offset, int size = -1)
    {
        throw "The type " << T << "cannot be decoded yet";
    }

    template<> FString EncodingUtility::Decode<FString>(TArray<uint8> bytes, int& offset, int size)
    {
        if (size == -1)
        {
            throw "In order to decode a string, the argument 'size' must be set";
        }
        FString decodedString = FString(UTF8_TO_TCHAR(bytes.GetData() + offset));
        offset += size;
        return decodedString;
    }

    template<> bool EncodingUtility::Decode<bool>(TArray<uint8> bytes, int& offset, int size)
    {
        bool decodedValue = *((bool*)(bytes.GetData() + offset));
        offset += sizeof(bool);
        return decodedValue;
    }

    template<> char EncodingUtility::Decode<char>(TArray<uint8> bytes, int& offset, int size)
    {
        char decodedValue = *((char*)(bytes.GetData() + offset));
        offset += sizeof(char);
        return decodedValue;
    }

    template<> double EncodingUtility::Decode<double>(TArray<uint8> bytes, int& offset, int size)
    {
        double decodedValue = *((double*)(bytes.GetData() + offset));
        offset += sizeof(double);
        return decodedValue;
    }

    template<> float EncodingUtility::Decode<float>(TArray<uint8> bytes, int& offset, int size)
    {
        float decodedValue = *((float*)(bytes.GetData() + offset));
        offset += sizeof(float);
        return decodedValue;
    }

    template<> int EncodingUtility::Decode<int>(TArray<uint8> bytes, int& offset, int size)
    {
        int decodedValue = *((int*)(bytes.GetData() + offset));
        offset += sizeof(int);
        return decodedValue;
    }

    template<> long EncodingUtility::Decode<long>(TArray<uint8> bytes, int& offset, int size)
    {
        long decodedValue = *((long*)(bytes.GetData() + offset));
        offset += sizeof(long);
        return decodedValue;
    }

    template<> short EncodingUtility::Decode<short>(TArray<uint8> bytes, int& offset, int size)
    {
        short decodedValue = *((short*)(bytes.GetData() + offset));
        offset += sizeof(short);
        return decodedValue;
    }

    template<> uint32 EncodingUtility::Decode<uint32>(TArray<uint8> bytes, int& offset, int size)
    {
        uint32 decodedValue = ((uint32)(bytes.GetData() + offset));
        offset += sizeof(uint32);
        return decodedValue;
    }

    template<> uint64 EncodingUtility::Decode<uint64>(TArray<uint8> bytes, int& offset, int size)
    {
        uint64 decodedValue = ((uint64)(bytes.GetData() + offset));
        offset += sizeof(uint64);
        return decodedValue;
    }

    template<> uint16 EncodingUtility::Decode<uint16>(TArray<uint8> bytes, int& offset, int size)
    {
        uint16 decodedValue = ((uint16)(bytes.GetData() + offset));
        offset += sizeof(uint16);
        return decodedValue;
    }

    template<> FVector3f EncodingUtility::Decode<FVector3f>(TArray<uint8> bytes, int& offset, int size)
    {
        return FVector3f(
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset));
    }

    template<> FIntVector EncodingUtility::Decode<FIntVector>(TArray<uint8> bytes, int& offset, int size)
    {
        return FIntVector(
            Decode<int>(bytes, offset),
            Decode<int>(bytes, offset),
            Decode<int>(bytes, offset));
    }

    template<> FVector2f EncodingUtility::Decode<FVector2f>(TArray<uint8> bytes, int& offset, int size)
    {
        return FVector2f(
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset));
    }

    template<> FIntVector2 EncodingUtility::Decode<FIntVector2>(TArray<uint8> bytes, int& offset, int size)
    {
        return FIntVector2(
            Decode<int>(bytes, offset),
            Decode<int>(bytes, offset));
    }

    template<> FQuat4f EncodingUtility::Decode<FQuat4f>(TArray<uint8> bytes, int& offset, int size)
    {
        return FQuat4f(
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset),
            Decode<float>(bytes, offset));
    }

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

#pragma region GetSizeOf

    template<typename T>
    int EncodingUtility::GetSizeOf(T value)
    {
        return sizeof(T);
    }

    template<>
    int EncodingUtility::GetSizeOf<FString>(FString value)
    {
        return Encode(value).Num();
    }

    template<> int EncodingUtility::GetSizeOf<FVector3f>(FVector3f value)
    {
        return 3 * sizeof(float);
    }

    template<> int EncodingUtility::GetSizeOf<FIntVector>(FIntVector value)
    {
        return 3 * sizeof(int);
    }

    template<> int EncodingUtility::GetSizeOf<FVector2f>(FVector2f value)
    {
        return 2 * sizeof(float);
    }

    template<> int EncodingUtility::GetSizeOf<FIntVector2>(FIntVector2 value)
    {
        return 2 * sizeof(int);
    }

    template<> int EncodingUtility::GetSizeOf<FQuat4f>(FQuat4f value)
    {
        return 4 * sizeof(float);
    }

#pragma endregion

#pragma region HasFixedEncodedSize
    template<typename T>
    bool EncodingUtility::HasFixedEncodedSize()
    {
        return true;
    }
    template<>
    bool EncodingUtility::HasFixedEncodedSize<FString>()
    {
        return false;
    }
#pragma endregion

#pragma region Debug
    FString EncodingUtility::GetBytesAsString(TArray<uint8> bytes)
    {
        FString returnValue;
        int byteCount = bytes.Num();
        for (int i = 0; i < byteCount; i++)
        {
            returnValue += FString::FromInt(bytes[i]) + (i < byteCount - 1 ? "|" : "");
        }
        return returnValue;
    }

    TArray<uint8> EncodingUtility::GetStringAsBytes(FString stringifiedBytes)
    {
        TArray<FString> splittedString;
        stringifiedBytes.ParseIntoArray(splittedString, TEXT("|"), true);

        TArray<uint8> bytes;
        bytes.SetNumUninitialized(splittedString.Num());
        for (int i = 0; i < splittedString.Num(); i++)
        {
            bytes[i] = FCString::Atoi(*splittedString[i]);
        }

        return bytes;
    }
#pragma endregion
}