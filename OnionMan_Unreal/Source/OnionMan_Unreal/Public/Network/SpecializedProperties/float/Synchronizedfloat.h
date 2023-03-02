// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedFloat.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFloat : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	float m_value;

public:
	USynchronizedFloat();
	USynchronizedFloat(float value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline float GetValue() const
    {
        return GetValueGeneric<float>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(float& newValue)
    {
        SetValueGeneric<float>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

