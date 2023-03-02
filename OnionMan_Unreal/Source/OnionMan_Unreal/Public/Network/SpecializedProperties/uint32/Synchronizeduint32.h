// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedUint32.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedUint32 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	uint32 m_value;

public:
	USynchronizedUint32();
	USynchronizedUint32(uint32 value, uint16 propertyID);

    inline uint32 GetValue() const
    {
        return GetValueGeneric<uint32>(m_value);
    }

    inline void SetValue(uint32& newValue)
    {
        SetValueGeneric<uint32>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

