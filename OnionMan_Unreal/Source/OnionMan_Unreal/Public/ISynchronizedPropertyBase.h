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

    virtual bool NeedSync();

    virtual uint16 PropertyID();

    virtual void Init();

    virtual int GetEncodedPropertySize();

    virtual void PutEncodedPoropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true);
    virtual TArray<uint8> EncodeProperty(bool forSync = true);

    virtual void DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize);
};