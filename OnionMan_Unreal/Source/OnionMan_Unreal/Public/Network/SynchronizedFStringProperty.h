// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedPropertyBase.h"

#include "SynchronizedFStringProperty.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USynchronizedFStringProperty : public UObject, public ISynchronizedPropertyBase
{
	GENERATED_BODY()
private:
	FString m_value;
	uint16 m_propertyID;

	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;

public:
	USynchronizedFStringProperty();
	USynchronizedFStringProperty(FString value, uint16 propertyID);
	~USynchronizedFStringProperty();

	UFUNCTION(BlueprintCallable)
	const FString& GetValue() const
	{
		return m_value;
	}

	UFUNCTION(BlueprintCallable)
	void SetValue(FString& value)
	{
		if (m_value != value)
		{
			m_value = value;
			m_needSync = true;

			m_sizeMayHaveChanged = true;
		}
	}

	// Hérité via ISynchronizedPropertyBase
	UFUNCTION(BlueprintCallable)
	virtual bool NeedSync() override;
	virtual const uint16 PropertyID() const override;
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual int GetEncodedPropertySize() override;
	UFUNCTION(BlueprintCallable)
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	UFUNCTION(BlueprintCallable)
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};
