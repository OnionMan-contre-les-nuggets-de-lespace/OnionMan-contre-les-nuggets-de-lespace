// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedBool.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedBool : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	bool m_value;

public:
	USynchronizedBool();
	USynchronizedBool(bool value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline bool GetValue() const
    {
        return GetValueGeneric<bool>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(bool& newValue)
    {
        SetValueGeneric<bool>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

