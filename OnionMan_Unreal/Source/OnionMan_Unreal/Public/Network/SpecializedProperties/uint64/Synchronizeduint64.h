// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedUint64.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedUint64 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	uint64 m_value;

public:
	USynchronizedUint64();
	USynchronizedUint64(uint64 value, uint16 propertyID);

    inline uint64 GetValue() const
    {
        return GetValueGeneric<uint64>(m_value);
    }

    inline void SetValue(uint64& newValue)
    {
        SetValueGeneric<uint64>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

