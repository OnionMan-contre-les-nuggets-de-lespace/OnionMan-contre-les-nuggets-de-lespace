// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"


#include "SynchronizedTCHAR.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedTCHAR : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	TCHAR m_value;

public:
	USynchronizedTCHAR();
	USynchronizedTCHAR(TCHAR value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const TCHAR& GetValue() const
    {
        return GetValueGeneric<TCHAR>(m_value);
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TCHAR& newValue)
    {
        GetValueGeneric<TCHAR>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

