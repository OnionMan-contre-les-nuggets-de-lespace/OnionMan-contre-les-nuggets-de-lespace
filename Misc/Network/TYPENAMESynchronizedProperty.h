// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "SynchronizedCLASSNAME.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedCLASSNAME : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	TYPENAME m_value;

public:
	USynchronizedCLASSNAME();
	USynchronizedCLASSNAME(TYPENAME value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline TYPENAME GetValue() const
    {
        return GetValueGeneric<TYPENAME>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(TYPENAME& newValue)
    {
        SetValueGeneric<TYPENAME>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};