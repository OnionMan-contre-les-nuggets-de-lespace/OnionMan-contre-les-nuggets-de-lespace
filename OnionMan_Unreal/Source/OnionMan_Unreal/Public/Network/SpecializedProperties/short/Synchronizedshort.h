// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "Synchronizedshort.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedshort : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	short m_value;

public:
	USynchronizedshort();
	USynchronizedshort(short value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const short& GetValue() const
    {
        return GetValueGeneric<short>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(short& newValue)
    {
        GetValueGeneric<short>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

