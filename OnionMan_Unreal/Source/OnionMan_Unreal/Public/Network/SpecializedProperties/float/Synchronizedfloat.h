// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "Synchronizedfloat.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedfloat : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	float m_value;

public:
	USynchronizedfloat();
	USynchronizedfloat(float value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const float& GetValue() const
    {
        return GetValueGeneric<float>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(float& newValue)
    {
        GetValueGeneric<float>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

