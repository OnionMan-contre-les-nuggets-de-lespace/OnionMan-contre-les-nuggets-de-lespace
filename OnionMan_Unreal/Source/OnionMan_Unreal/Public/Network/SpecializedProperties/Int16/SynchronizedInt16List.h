// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedInt16List.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedInt16List : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<int16> m_value{};
	TArray<int16> m_previousValue{};

public:
	USynchronizedInt16List();
	USynchronizedInt16List(TArray<int16>& initialValue, uint16 propertyID);

    inline void GetValue(TArray<int16>& outValue) const
    {
		outValue = m_value;
    }

    inline void SetValue(TArray<int16>& newValue)
    {
        SetValueGeneric<int16>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

