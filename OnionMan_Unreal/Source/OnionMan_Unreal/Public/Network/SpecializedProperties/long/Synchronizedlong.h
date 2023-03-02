// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "Synchronizedlong.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedlong : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	long m_value;

public:
	USynchronizedlong();
	USynchronizedlong(long value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const long& GetValue() const
    {
        return GetValueGeneric<long>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(long& newValue)
    {
        GetValueGeneric<long>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

