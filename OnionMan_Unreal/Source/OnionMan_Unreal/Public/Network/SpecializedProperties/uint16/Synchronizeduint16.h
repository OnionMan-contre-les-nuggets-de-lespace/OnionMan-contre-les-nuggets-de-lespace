// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "Synchronizeduint16.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizeduint16 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	uint16 m_value;

public:
	USynchronizeduint16();
	USynchronizeduint16(uint16 value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const uint16& GetValue() const
    {
        return GetValueGeneric<uint16>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(uint16& newValue)
    {
        SetValueGeneric<uint16>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

