// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "Runtime/Core/Public/Math/Vector.h" 

#include "SynchronizedFVector2f.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFVector2f : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	FVector2f m_value;

public:
	USynchronizedFVector2f();
	USynchronizedFVector2f(FVector2f value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const FVector2f& GetValue() const
    {
        return GetValueGeneric<FVector2f>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(FVector2f& newValue)
    {
        GetValueGeneric<FVector2f>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

