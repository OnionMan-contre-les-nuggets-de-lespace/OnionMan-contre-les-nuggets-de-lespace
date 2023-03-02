// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedInt.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedInt : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	int m_value;

public:
	USynchronizedInt();
	USynchronizedInt(int value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline int GetValue() const
    {
        return GetValueGeneric<int>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(int& newValue)
    {
        SetValueGeneric<int>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

