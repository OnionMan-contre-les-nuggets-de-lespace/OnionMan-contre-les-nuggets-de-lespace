// Fill out your copyright notice in the Description page of Project Settings.
// Credits : https://jeremybois.gitlab.io/nfp121-cnam-cpp/content/07-Architecture/Architecture.html#singleton-patron

#pragma once

#include "CoreMinimal.h"
#include "ISynchronizedObjectBase.h"

//#include "NetworkManager.generated.h"

/**
 * 
 */
//UCLASS()
class ONIONMAN_UNREAL_API NetworkManager
{
    //GENERATED_BODY();
private:
    TMap<uint32, ISynchronizedObjectBase*> m_synchronizedObjects{};
    TArray<ISynchronizedObjectBase*> m_objectsArray{};

public:
    // Singleton stuff
    static NetworkManager& Instance();

    ~NetworkManager();

    NetworkManager(const NetworkManager&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    NetworkManager(NetworkManager&&) = delete;
    NetworkManager& operator=(NetworkManager&&) = delete;

    // NetworkManager methods
    void AddSynchronizedObject(ISynchronizedObjectBase& obj);
    void GetObjectsToSync(TArray<TTuple<ISynchronizedObjectBase*, int>>& outObjectsToSync);
    void EncodeObjects(TArray<uint8>& outEncodedObjects);
    void DecodeObjects(TArray<uint8>& encodedObjects);


private:
    NetworkManager(); 
};
