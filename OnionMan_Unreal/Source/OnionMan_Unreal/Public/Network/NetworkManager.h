// Fill out your copyright notice in the Description page of Project Settings.
// Credits : https://jeremybois.gitlab.io/nfp121-cnam-cpp/content/07-Architecture/Architecture.html#singleton-patron

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedObjectBase.h"

#include "NetworkManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ONIONMAN_UNREAL_API UNetworkManager : public UObject
{
    GENERATED_BODY()
private:
    TMap<uint32, TObjectPtr<ISynchronizedObjectBase>> m_synchronizedObjects{};
    TArray<TObjectPtr<ISynchronizedObjectBase>> m_objectsArray{};

public:
    // NetworkManager methods
    
    void AddSynchronizedObject(ISynchronizedObjectBase& obj);
    void GetObjectsToSync(TArray<TTuple<TObjectPtr<ISynchronizedObjectBase>, int>>& outObjectsToSync);
    void EncodeObjects(TArray<uint8>& outEncodedObjects);
    void DecodeObjects(TArray<uint8>& encodedObjects);

    void EndPlay();


private:
    UNetworkManager(); 
};
