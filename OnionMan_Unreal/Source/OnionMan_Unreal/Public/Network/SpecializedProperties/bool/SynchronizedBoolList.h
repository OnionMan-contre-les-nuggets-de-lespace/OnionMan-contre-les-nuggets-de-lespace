// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedBoolList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedBoolList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	TArray<bool> m_value{};

private:
	TArray<bool> m_previousValue{};

public:
	USynchronizedBoolList();
	USynchronizedBoolList(TArray<bool>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<bool>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(UPARAM(ref) TArray<bool>& newValue)
    {
        SetValueGeneric<bool>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

