// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../SpecializedSynchronizedList.h"


#include "SynchronizedCLASSNAMEList.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class ONIONMAN_UNREAL_API USynchronizedCLASSNAMEList : public USpecializedSynchronizedList
{
	GENERATED_BODY()
private:
	TArray<TYPENAME> m_value{};
	TArray<TYPENAME> m_previousValue{};

public:
	USynchronizedCLASSNAMEList();
	USynchronizedCLASSNAMEList(TArray<TYPENAME>& initialValue, uint16 propertyID);

    UFUNCTION(BlueprintCallable)
    inline void GetValue(TArray<TYPENAME>& outValue) const
    {
		outValue = m_value;
    }

    UFUNCTION(BlueprintCallable)
    inline void SetValue(TArray<TYPENAME>& newValue)
    {
        SetValueGeneric<TYPENAME>(newValue, m_value);
    }

	virtual void Init() override;
	virtual int GetEncodedPropertySize() override;
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;

protected:
	virtual void CheckNeedSync() override;
};