// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedFloatList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedFloatList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	TArray<float> m_value{};

private:
	TArray<float> m_previousValue{};

public:
	USynchronizedFloatList();
	USynchronizedFloatList(TArray<float>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<float>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(UPARAM(ref) TArray<float>& newValue)
    {
        SetValueGeneric<float>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

