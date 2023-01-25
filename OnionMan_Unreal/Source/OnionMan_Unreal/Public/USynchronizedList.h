// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedPropertyBase.h"

/**
 * 
 */
template <typename T>
class ONIONMAN_UNREAL_API USynchronizedList : public ISynchronizedPropertyBase
{
private:
	uint16 m_propertyID;

	TArray<T> m_value;

	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
    TArray<T> m_previousValue;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;

	int GetTSize(T element); 
	static bool ListEquals(TArray<T> self, TArray<T> other); 
	static TArray<T> Copy(TArray<T> listToCopy) const;
	void CheckNeedSync();

public:
	USynchronizedList(TArray<T> initialValue, uint16 propertyID);
	~USynchronizedList();

	bool NeedSync() override;

    const uint16 PropertyID() const override;
	
	const TArray<T>& GetValue() const;
	void SetValue(TArray<T> value);

    void Init() override;

    int GetEncodedPropertySize() override;

    void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override;
    const TArray<uint8>& EncodeProperty(bool forSync = true) override;

    void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};
