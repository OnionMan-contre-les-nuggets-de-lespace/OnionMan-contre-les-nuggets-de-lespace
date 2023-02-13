// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedPropertyBase.h"


/**
 *
 */
template<typename T>
class ONIONMAN_UNREAL_API USynchronizedProperty : public ISynchronizedPropertyBase
{
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
	USynchronizedProperty(T value, uint16 propertyID);

	bool NeedSync() override;

	const uint16 PropertyID() const override;

	inline const T& GetValue() const
	{
		return m_value;
	}

	inline void SetValue(T value)
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
