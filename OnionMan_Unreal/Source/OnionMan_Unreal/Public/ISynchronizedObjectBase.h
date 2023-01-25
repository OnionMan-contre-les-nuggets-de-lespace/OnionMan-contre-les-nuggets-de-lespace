// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedPropertyBase.h"

#include "ISynchronizedObjectBase.generated.h"

/**
    *
    */
UINTERFACE()
class USynchronizedObjectBase : public UInterface
{
    GENERATED_BODY()
};

struct ObjectNeedSyncResult
{
private:
    bool m_needSync;
    int m_encodedSize;

public:
    inline bool NeedSync()
    {
        return m_needSync;
    }

    inline int EncodedSize()
    {
        return m_encodedSize;
    }

    inline ObjectNeedSyncResult(bool needSync, int encodedSize)
    {
        m_needSync = needSync;
        m_encodedSize = encodedSize;
    }
};

/**
    *
    */
class ONIONMAN_UNREAL_API ISynchronizedObjectBase
{
    GENERATED_BODY()
public:
    const uint32 ObjectID() const = 0;

    const TMap<uint16, ISynchronizedPropertyBase&> Properties() const = 0;

    ObjectNeedSyncResult NeedSync() = 0;

    void PutEncodedObjectToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) = 0;
    TArray<uint8>& EncodeObject(bool forSync = true) = 0;

    void DecodeObject(TArray<uint8>& encodedProperties, int& offset, int size) = 0;

    void LoadProperties() = 0;
};