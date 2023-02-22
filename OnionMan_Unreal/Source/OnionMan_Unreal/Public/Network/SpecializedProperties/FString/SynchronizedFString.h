// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedProperty.h"

#include "SynchronizedFString.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFString : public USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	FString m_value;

public:
	USynchronizedFString();
	USynchronizedFString(FString value, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline const FString GetValue() const
    {
        return m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void GetValue(FString& newValue)
    {
        if (m_value != value)
        {
            m_value = value;
            m_sizeMayHaveChanged = true;
            m_needSync = true;
        }
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

