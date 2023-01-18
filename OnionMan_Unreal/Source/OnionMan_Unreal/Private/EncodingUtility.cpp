#include "EncodingUtility.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Core/Public/Math/Quat.h"
#include "Runtime/Core/Public/Math/IntVector.h"

namespace OnionMan::Network 
{
    template <typename T> TArray<uint8> EncodingUtility::Encode(T value)
    {
        throw "The type " << T << "cannot be encoded yet";
    }

#pragma region Encode
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

#pragma endregion

    template <typename T> T EncodingUtility::Decode(TArray<uint8> bytes, int& offset, int size = -1)
    {
        throw "The type " << T << "cannot be decoded yet";
    }

#pragma region Decode

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



