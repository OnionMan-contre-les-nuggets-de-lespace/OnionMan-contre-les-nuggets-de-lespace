// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedPropertyBase.h"

/**
 * 
 */
class ONIONMAN_UNREAL_API USpecializedSynchronizedList : public UObject, public ISynchronizedPropertyBase
{
private:
	uint16 m_propertyID;

	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;



	void CheckNeedSync();

public:
	USynchronizedList(TArray<T> initialValue, uint16 propertyID)
	{
		m_value = Copy(initialValue);
		m_propertyID = propertyID;
	}

	bool NeedSync() override
    {
        return m_needSync;
    };

    const uint16 PropertyID() const override
    {
        return m_propertyID;
    };
	
	const TArray<T>& GetValue() const
	{
		return m_value;
	}

	void SetValue(TArray<T> value)
	{
		m_value = value;
	}

    void Init() override;

    int GetEncodedPropertySize() override;

    void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override;

    void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

#pragma region Utils
protected:
    template <typename T>
	int GetTSize(T element)
	{
		if (m_hasTAFixedSize)
		{
			return m_fixedTSize;
		}
		return EncodingUtility::GetSizeOf<T>(&element);
	}

    template <typename T>
	bool ListEquals(TArray<T>& self, TArray<T>& other)
	{
		if (self == nullptr || other == nullptr)
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
		if (fromList == nullptr)
		{
			return nullptr;
		}

		toList.Empty();
		toList.Reserve(fromList.GetAllocatedSize());

		for (T item : fromList)
		{
			toList.Add(item);
		}
	}
#pragma endregion
};
