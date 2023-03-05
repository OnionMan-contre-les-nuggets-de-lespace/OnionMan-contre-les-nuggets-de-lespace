// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "Runtime/Core/Public/Math/Quat.h" 

#include "SynchronizedFQuat4f.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedFQuat4f : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	FQuat4f m_value;

public:
	USynchronizedFQuat4f();
	USynchronizedFQuat4f(FQuat4f value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline FQuat4f GetValue() const
    {
        return GetValueGeneric<FQuat4f>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(FQuat4f& newValue)
    {
        SetValueGeneric<FQuat4f>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

