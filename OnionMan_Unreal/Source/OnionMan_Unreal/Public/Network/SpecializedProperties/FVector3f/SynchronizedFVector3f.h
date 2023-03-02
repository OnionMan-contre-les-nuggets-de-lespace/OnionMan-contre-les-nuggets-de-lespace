// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "Runtime/Core/Public/Math/Vector.h" 

#include "SynchronizedFVector3f.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFVector3f : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	FVector3f m_value;

public:
	USynchronizedFVector3f();
	USynchronizedFVector3f(FVector3f value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const FVector3f& GetValue() const
    {
        return GetValueGeneric<FVector3f>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(FVector3f& newValue)
    {
        GetValueGeneric<FVector3f>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

