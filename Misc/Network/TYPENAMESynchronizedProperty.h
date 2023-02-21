// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SpecializedSynchronizedProperty.h"

#include "TYPENAMESynchronizedProperty.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ONIONMAN_UNREAL_API UTYPENAMESynchronizedProperty : USpecializedSynchronizedProperty
{
	GENERATED_BODY()
private:
	TYPENAME m_value;

public:
	UTYPENAMESynchronizedProperty();
	UTYPENAMESynchronizedProperty(TYPENAME value, uint16 propertyID);

	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual int GetEncodedPropertySize() override;
	UFUNCTION(BlueprintCallable)
	virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync) override;
	UFUNCTION(BlueprintCallable)
	virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override;
};

