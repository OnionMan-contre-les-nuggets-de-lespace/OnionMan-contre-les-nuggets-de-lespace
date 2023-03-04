// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedUint16List.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedUint16List : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<uint16> m_value{};
	TArray<uint16> m_previousValue{};

public:
	USynchronizedUint16List();
	USynchronizedUint16List(TArray<uint16>& initialValue, uint16 propertyID);

    inline void GetValue(TArray<uint16>& outValue) const
    {
		outValue = m_value;
    }

    inline void SetValue(TArray<uint16>& newValue)
    {
        SetValueGeneric<uint16>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

