// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedInt16.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedInt16 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	int16 m_value;

public:
	USynchronizedInt16();
	USynchronizedInt16(int16 value, uint16 propertyID);

    inline int16 GetValue() const
    {
        return GetValueGeneric<int16>(m_value);
    }

    inline void SetValue(int16& newValue)
    {
        SetValueGeneric<int16>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

