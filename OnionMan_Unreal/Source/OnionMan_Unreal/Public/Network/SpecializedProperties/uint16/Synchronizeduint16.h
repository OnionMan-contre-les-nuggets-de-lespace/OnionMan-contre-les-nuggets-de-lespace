// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedUint16.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedUint16 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	uint16 m_value;

public:
	USynchronizedUint16();
	USynchronizedUint16(uint16 value, uint16 propertyID);

    inline uint16 GetValue() const
    {
        return GetValueGeneric<uint16>(m_value);
    }

    inline void SetValue(uint16& newValue)
    {
        SetValueGeneric<uint16>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

