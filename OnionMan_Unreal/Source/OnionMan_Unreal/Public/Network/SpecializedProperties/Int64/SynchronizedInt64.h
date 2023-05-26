// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedInt64.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedInt64 : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	int64 m_value;

public:
	USynchronizedInt64();
	USynchronizedInt64(int64 value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline int64 GetValue() const
    {
        return GetValueGeneric<int64>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(UPARAM(ref) int64& newValue)
    {
        SetValueGeneric<int64>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

