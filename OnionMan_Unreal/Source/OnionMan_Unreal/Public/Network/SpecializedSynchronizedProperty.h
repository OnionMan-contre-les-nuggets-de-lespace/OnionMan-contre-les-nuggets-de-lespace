﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedPropertyBase.h"
#include "EncodingUtility.h"

#include "SpecializedSynchronizedProperty.generated.h"

using namespace OnionMan::Network;

/**
 *
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USpecializedSynchronizedProperty : public UObject, public ISynchronizedPropertyBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, DisplayName = "Role")
	NetworkRole m_role = NetworkRole::SenderAndReciever;

	UPROPERTY(EditAnywhere, DisplayName = "Property ID")
	uint16 m_propertyID{};

private:
	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;

public:
	USpecializedSynchronizedProperty();
	USpecializedSynchronizedProperty(uint16 propertyID);

	// Inherited from ISynchronizedPropertyBase
	UFUNCTION(BlueprintCallable)
	virtual bool NeedSync() override;
	// Cannot use UFUNCTION(BlueprintCallable) because blueprints does not support uint16
	virtual const uint16 PropertyID() const override;
	UFUNCTION(BlueprintCallable)
	virtual NetworkRole Role() const override;

	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual int GetEncodedPropertySize() override;
	UFUNCTION(BlueprintCallable)
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	UFUNCTION(BlueprintCallable)
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	// Generic functions that will be called from the specialized classes 
#pragma region Generic
	template<typename T>
	const T& GetValueGeneric(const T& value) const
	{
        if (Role() == NetworkRole::Sender)
        {
            LOG_ERROR("You should not try to get the value of a sender property");
        }
		return value;
	}

	template<typename T>
	void SetValueGeneric(const T& value, T& outValue)
	{
        if (Role() == NetworkRole::Reciever)
        {
            LOG_ERROR("Do not set the value of a reciever property");
            return;
        }
		if (outValue != value)
		{
			outValue = value;
			m_sizeMayHaveChanged = true;
			m_needSync = true;
		}
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
	int GetEncodedPropertySizeGeneric(T& value)
	{
		if (m_hasFixedSize)
		{
			return sizeof(int) + sizeof(uint16) + m_fixedSize; // Size + ID + Data
		}

		if (m_sizeMayHaveChanged)
		{
			m_sizeMayHaveChanged = false;
			m_encodedSize = sizeof(int) + sizeof(uint16) + EncodingUtility::GetSizeOf<T>(&value); // Size + ID + Data
		}
		return m_encodedSize;
	}

	template<typename T>
	void PutEncodedPropertyToBufferGeneric(T& propertyValue, TArray<uint8>& buffer, int& offset, bool forSync)
	{
		if (forSync)
		{
            if (Role() == NetworkRole::Reciever)
            {
                LOG_ERROR("Do not try to encode a reciever property");
                return;
            }
			m_needSync = false;
		}

		EncodingUtility::PutEncodedValueInBuffer<int>(GetEncodedPropertySize() - sizeof(int), buffer, offset); // Put Size
		EncodingUtility::PutEncodedValueInBuffer<uint16>(m_propertyID, buffer, offset);                        // Put ID
		EncodingUtility::PutEncodedValueInBuffer<T>(propertyValue, buffer, offset);
	}

	template<typename T>
	void DecodePropertyGeneric(T& outValue, TArray<uint8>& encodedProperty, int& offset, int propertySize)
	{
		T decodedValue = EncodingUtility::Decode<T>(encodedProperty, offset, propertySize);

        if (Role() == NetworkRole::Sender)
        {
            LOG_ERROR("Do not try to decode a sender property");
            return;
        }
        
		if (outValue != decodedValue)
		{
			LOG_WARNING("Value changed")
			outValue = decodedValue;
            m_sizeMayHaveChanged = true;
			// if (m_onValueChanged != null)
			// {
			//     m_onValueChanged(m_value);
			// }
		}
	}
#pragma endregion

};

