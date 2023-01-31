// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedPropertyBase.h"

#include "USynchronizedProperty.generated.h"

/**
 *
 */
template<typename T>
UCLASS()
class ONIONMAN_UNREAL_API USynchronizedProperty : public ISynchronizedPropertyBase
{
	GENERATED_BODY()


private:
	T m_value;
	uint16 m_propertyID;

	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;

public:
	USynchronizedProperty();
	USynchronizedProperty(T value, uint16 propertyID)
	{
		m_value = value;
		m_propertyID = propertyID;
	}
	~USynchronizedProperty();

	bool NeedSync() override;

	const uint16 PropertyID() const override;

	const T& GetValue() const
	{
		return m_value;
	}
	void SetValue(T value)
	{
		if (m_value != value)
		{
			m_value = value;
			m_needSync = true;

			m_sizeMayHaveChanged = true;
		}
	}

	void Init() override;

	int GetEncodedPropertySize() override;

	void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override;

	void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

};
