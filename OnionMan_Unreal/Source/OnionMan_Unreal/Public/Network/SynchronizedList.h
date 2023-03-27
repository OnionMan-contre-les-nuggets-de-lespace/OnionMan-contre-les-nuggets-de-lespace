// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedPropertyBase.h"

/**
 * 
 */
template <typename T>
class ONIONMAN_UNREAL_API USynchronizedList : public ISynchronizedPropertyBase
{
private:
    NetworkRole m_role;

	uint16 m_propertyID;

	TArray<T> m_value;

	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
    TArray<T> m_previousValue;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;

#pragma region Utils
	int GetTSize(T element)
	{
		if (m_hasTAFixedSize)
		{
			return m_fixedTSize;
		}
		return EncodingUtility::GetSizeOf<T>(&element);
	}

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

	void CheckNeedSync();

public:
	USynchronizedList(TArray<T> initialValue, uint16 propertyID)
	{
		m_value = Copy(initialValue);
		m_propertyID = propertyID;
	}

	~USynchronizedList();

	bool NeedSync() override;

    const NetworkRole Role() const override
    {
        return m_role;
    }

    const uint16 PropertyID() const override;
	
	const TArray<T>& GetValue() const
	{
        if (Role() == NetworkRole::Sender)
        {
            LOG_ERROR("You should not try to get the value of a sender property");
        }
		return m_value;
	}

	void SetValue(TArray<T> value)
	{
        if (Role() == NetworkRole::Reciever)
        {
            LOG_ERROR("Do not set the value of a reciever property");
            return;
        }
		m_value = value;
	}

    void Init() override;

    int GetEncodedPropertySize() override;

    void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override;

    void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};
