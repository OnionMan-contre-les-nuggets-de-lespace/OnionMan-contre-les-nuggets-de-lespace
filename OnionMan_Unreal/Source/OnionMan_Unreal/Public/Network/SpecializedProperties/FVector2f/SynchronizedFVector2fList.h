// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"

#include "Runtime/Core/Public/Math/Vector.h" 

#include "SynchronizedFVector2fList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedFVector2fList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	TArray<FVector2f> m_value{};

private:
	TArray<FVector2f> m_previousValue{};

public:
	USynchronizedFVector2fList();
	USynchronizedFVector2fList(TArray<FVector2f>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<FVector2f>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(UPARAM(ref) TArray<FVector2f>& newValue)
    {
        SetValueGeneric<FVector2f>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

