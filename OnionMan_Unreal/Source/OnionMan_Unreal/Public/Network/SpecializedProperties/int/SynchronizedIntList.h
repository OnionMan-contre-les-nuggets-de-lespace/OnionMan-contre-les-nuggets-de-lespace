// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedIntList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedIntList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<int> m_value{};
	TArray<int> m_previousValue{};

public:
	USynchronizedIntList();
	USynchronizedIntList(TArray<int>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<int>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(TArray<int>& newValue)
    {
        SetValueGeneric<int>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

