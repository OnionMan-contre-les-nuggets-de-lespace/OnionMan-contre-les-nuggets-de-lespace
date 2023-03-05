// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedDouble.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedDouble : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	double m_value;

public:
	USynchronizedDouble();
	USynchronizedDouble(double value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline double GetValue() const
    {
        return GetValueGeneric<double>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(double& newValue)
    {
        SetValueGeneric<double>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

