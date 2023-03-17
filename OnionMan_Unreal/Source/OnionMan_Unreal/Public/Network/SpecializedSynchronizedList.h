// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedPropertyBase.h"
#include "Network/EncodingUtility.h"

#include "SpecializedSynchronizedList.generated.h"

using namespace OnionMan::Network;

/**
 * 
 */
UCLASS()
class ONIONMAN_UNREAL_API USpecializedSynchronizedList : public UObject, public ISynchronizedPropertyBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, DisplayName = "Property ID")
    uint16 m_propertyID;

private:
    bool m_needSync = false;

    bool m_hasFixedSize = false;
    int m_fixedSize = 0;

    // Action<T> m_onValueChanged;
    bool m_sizeMayHaveChanged = true;
    int m_encodedSize;


public:
    USpecializedSynchronizedList();
    USpecializedSynchronizedList(uint16 propertyID);

    // Inherited from ISynchronizedPropertyBase
    UFUNCTION(BlueprintCallable)
    virtual bool NeedSync() override;
    // Cannot use UFUNCTION(BlueprintCallable) because blueprints does not support uint16
    virtual const uint16 PropertyID() const override;
    UFUNCTION(BlueprintCallable)
    virtual void Init() override;
    UFUNCTION(BlueprintCallable)
    virtual int GetEncodedPropertySize() override;
    UFUNCTION(BlueprintCallable)
    virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
    UFUNCTION(BlueprintCallable)
    virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:

    virtual void CheckNeedSync();

#pragma region Utils
    template <typename T>
    int GetTSize(T element)
    {
        if (m_hasFixedSize)
        {
            return m_fixedSize;
        }
        return EncodingUtility::GetSizeOf<T>(&element);
    }

    template <typename T>
    bool ListEquals(TArray<T>& self, TArray<T>& other)
    {
        if (&self == nullptr || &other == nullptr)
        {
            return false;
        }

        if (other.Num() != self.Num())
        {
            return false;
        }

        for (int i = 0; i < self.Num(); i++)
        {
            if (self[i] != other[i])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    void CopyTo(TArray<T>& fromList, TArray<T>& toList)
    {
        if (&fromList == nullptr || &toList == nullptr)
        {
            return;
        }
        toList.Empty();
        toList.Reserve(fromList.GetAllocatedSize());

        for (T item : fromList)
        {
            toList.Add(item);
        }
    }
#pragma endregion	
// Generic functions that will be called from the specialized classes 
#pragma region Generic
    template<typename T>
    const TArray<T>& GetValueGeneric(const TArray<T>& value) const
    {
        return value;
    }

    template<typename T>
    void SetValueGeneric(TArray<T> value, TArray<T>& outValue)
    {
        outValue = value;
    }
    
    template<typename T>
    void InitGeneric()
    {
        m_hasFixedSize = EncodingUtility::HasFixedEncodedSize<T>();
        if (m_hasFixedSize)
        {
            m_fixedSize = EncodingUtility::GetSizeOf<T>();
        }
        else
        {
            m_sizeMayHaveChanged = true;
        }
    }

    template<typename T>
    int GetEncodedPropertySizeGeneric(TArray<T>& value)
    {
        if (m_hasFixedSize)
        {
            int encodedTSize = sizeof(int) + m_fixedSize; // Size + Data
            return sizeof(int) + sizeof(uint16) + encodedTSize * value.Num(); // Size + ID + Each element Size * n
        }

        if (m_sizeMayHaveChanged)
        {
            m_sizeMayHaveChanged = false;
            m_encodedSize = sizeof(int) + sizeof(uint16); // Property size + PropertyID
            for (T element : value)
            {
                m_encodedSize += sizeof(int) + GetTSize<T>(element); // each element size + Data
            }
        }
        return m_encodedSize;
    }

    template<typename T>
    void PutEncodedPropertyToBufferGeneric(TArray<T>& propertyValue, TArray<uint8>& buffer, int& offset, bool forSync)
    {
        if (forSync)
        {
            m_needSync = false;
        }

        EncodingUtility::PutEncodedValueInBuffer<int>(GetEncodedPropertySize() - sizeof(int), buffer, offset); // Put Size
        EncodingUtility::PutEncodedValueInBuffer<uint16>(m_propertyID, buffer, offset);                        // Put ID
        for (T item : propertyValue)                                                                           // For each element in list :
        {
            EncodingUtility::PutEncodedValueInBuffer<int>(GetTSize(item), buffer, offset);                     // Put Size
            EncodingUtility::PutEncodedValueInBuffer<T>(item, buffer, offset);                                 // Put Data
        }
    }

    template<typename T>
    void DecodePropertyGeneric(TArray<T>& outValue, TArray<T>& outPreviousValue, TArray<uint8>& encodedProperty, int& offset, int propertySize)
    {
        int propertyStartOffset = offset;
        TArray<T> decodedList {};

        while (offset < propertyStartOffset + propertySize) 
        {
            int itemSize = EncodingUtility::Decode<int>(encodedProperty, offset);
            decodedList.Add(EncodingUtility::Decode<T>(encodedProperty, offset, itemSize));
        }

        if (!ListEquals<T>(outValue, decodedList))
        {
            CopyTo<T>(decodedList, outValue);
            CopyTo<T>(decodedList, outPreviousValue);
            m_sizeMayHaveChanged = true;
            // if (m_onValueChanged != null)
            // {
            //     m_onValueChanged(m_value);
            // }
        }
    }

    template<typename T>
    void CheckNeedSyncGeneric(TArray<T>& value, TArray<T>& previousValue)
    {
        if (m_needSync)
        {
            return;
        }

        if (ListEquals<T>(value, previousValue))
        {
            m_needSync = false;
            return;
        }

        m_sizeMayHaveChanged = true;
        CopyTo<T>(value, previousValue);
        m_needSync = true;
    }
#pragma endregion
};
