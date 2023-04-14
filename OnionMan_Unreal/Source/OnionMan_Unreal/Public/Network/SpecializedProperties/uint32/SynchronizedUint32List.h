// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedUint32List.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedUint32List : public USpecializedSynchronizedList
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, DisplayName = "Value")
	TArray<uint32> m_value{};

private:
	TArray<uint32> m_previousValue{};

public:
	USynchronizedUint32List();
	USynchronizedUint32List(TArray<uint32>& initialValue, uint16 propertyID);

    inline void GetValue(TArray<uint32>& outValue) const
    {
		outValue = m_value;
    }

    inline void SetValue(TArray<uint32>& newValue)
    {
        SetValueGeneric<uint32>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

