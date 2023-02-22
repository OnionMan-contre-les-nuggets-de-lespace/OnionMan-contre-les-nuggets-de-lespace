// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "Synchronizeduint64.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizeduint64 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	uint64 m_value;

public:
	USynchronizeduint64();
	USynchronizeduint64(uint64 value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const uint64 GetValue() const
    {
        return m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(uint64& newValue)
    {
        if (m_value != value)
        {
            m_value = value;
            m_sizeMayHaveChanged = true;
            m_needSync = true;
        }
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

