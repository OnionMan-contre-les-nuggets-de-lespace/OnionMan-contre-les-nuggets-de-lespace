// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"

#include "Runtime/Core/Public/Math/IntVector.h" 

#include "SynchronizedFIntVector2List.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFIntVector2List : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<FIntVector2> m_value{};
	TArray<FIntVector2> m_previousValue{};

public:
	USynchronizedFIntVector2List();
	USynchronizedFIntVector2List(TArray<FIntVector2>& initialValue, uint16 propertyID);

    inline void GetValue(TArray<FIntVector2>& outValue) const
    {
		outValue = m_value;
    }

    inline void SetValue(TArray<FIntVector2>& newValue)
    {
        SetValueGeneric<FIntVector2>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};

