// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedPropertyBase.h"

#include "SpecializedSynchronizedProperty.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API USpecializedSynchronizedProperty : public UObject, public ISynchronizedPropertyBase
{
	GENERATED_BODY()
private:
	uint16 m_propertyID;

	bool m_needSync = false;

	bool m_hasFixedSize = false;
	int m_fixedSize = 0;

	// Action<T> m_onValueChanged;
	bool m_sizeMayHaveChanged = true;
	int m_encodedSize;

public:
	USpecializedSynchronizedProperty();
	USpecializedSynchronizedProperty(uint16 propertyID);

	

	// H�rit� via ISynchronizedPropertyBase
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

protected:
// Generic functions that will be called from the specialized classes 
	template<typename T>
    void InitGeneric();
	template<typename T>
	int GetEncodedPropertySizeGeneric(T& value);
	template<typename T>
	void PutEncodedPropertyToBufferGeneric(T& propertyValue, TArray<uint8>& buffer, int& offset, bool forSync);
	template<typename T>
	void DecodePropertyGeneric(T& outValue, TArray<uint8>& encodedProperty, int& offset, int propertySize);
};

