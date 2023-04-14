// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedDoubleList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedDoubleList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	TArray<double> m_value{};

private:
	TArray<double> m_previousValue{};

public:
	USynchronizedDoubleList();
	USynchronizedDoubleList(TArray<double>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<double>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(TArray<double>& newValue)
    {
        SetValueGeneric<double>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

