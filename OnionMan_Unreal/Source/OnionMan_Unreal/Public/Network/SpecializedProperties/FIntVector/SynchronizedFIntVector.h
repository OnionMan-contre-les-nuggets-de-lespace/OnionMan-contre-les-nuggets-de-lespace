// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "Runtime/Core/Public/Math/IntVector.h" 

#include "SynchronizedFIntVector.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFIntVector : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	FIntVector m_value;

public:
	USynchronizedFIntVector();
	USynchronizedFIntVector(FIntVector value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline FIntVector GetValue() const
    {
        return GetValueGeneric<FIntVector>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(FIntVector& newValue)
    {
        SetValueGeneric<FIntVector>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

