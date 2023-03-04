// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedUint64List.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedUint64List : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<uint64> m_value{};
	TArray<uint64> m_previousValue{};

public:
	USynchronizedUint64List();
	USynchronizedUint64List(TArray<uint64>& initialValue, uint16 propertyID);

    inline void GetValue(TArray<uint64>& outValue) const
    {
		outValue = m_value;
    }

    inline void SetValue(TArray<uint64>& newValue)
    {
        SetValueGeneric<uint64>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

