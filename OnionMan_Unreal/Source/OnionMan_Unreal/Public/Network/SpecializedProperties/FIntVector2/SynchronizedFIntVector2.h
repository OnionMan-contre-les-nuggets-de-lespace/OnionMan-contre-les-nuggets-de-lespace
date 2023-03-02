// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "Runtime/Core/Public/Math/IntVector.h" 

#include "SynchronizedFIntVector2.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFIntVector2 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	FIntVector2 m_value;

public:
	USynchronizedFIntVector2();
	USynchronizedFIntVector2(FIntVector2 value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const FIntVector2& GetValue() const
    {
        return GetValueGeneric<FIntVector2>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(FIntVector2& newValue)
    {
        SetValueGeneric<FIntVector2>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

