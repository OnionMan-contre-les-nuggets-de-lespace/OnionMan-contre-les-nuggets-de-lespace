// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ISynchronizedPropertyBase.generated.h"

/**
 *
 */
UINTERFACE()
class USynchronizedPropertyBase : public UInterface
{
    GENERATED_BODY()
};

class ISynchronizedPropertyBase
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable)
    virtual bool NeedSync() = 0;

    UFUNCTION(BlueprintCallable)
    virtual const uint16 PropertyID() const = 0 ;

    UFUNCTION(BlueprintCallable)
    virtual void Init() = 0;

    UFUNCTION(BlueprintCallable)
    virtual int GetEncodedPropertySize() = 0;

    UFUNCTION(BlueprintCallable)
    virtual void PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) = 0;

    UFUNCTION(BlueprintCallable)
    virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) = 0;
};