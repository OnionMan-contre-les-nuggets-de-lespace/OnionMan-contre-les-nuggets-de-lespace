// Fill out your copyright notice in the Description page of Project Settings.
// Credits : https://jeremybois.gitlab.io/nfp121-cnam-cpp/content/07-Architecture/Architecture.html#singleton-patron

#pragma once

#include "CoreMinimal.h"
#include "Network/ISynchronizedObjectBase.h"
#include "Network/NetworkBatch.h"

#include "NetworkManager.generated.h"


class BatchInfos
{
public:
    TArray<TObjectPtr<ISynchronizedObjectBase>> ObjectsToSync;
    int BatchSize;

    BatchInfos(TArray<TObjectPtr<ISynchronizedObjectBase>> objects, int batchSize)
    {
        ObjectsToSync = objects;
        BatchSize = batchSize;
    }
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ONIONMAN_UNREAL_API UNetworkManager : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FString AcknoledgeMessage = "ServerAck";

private:
    TMap<uint32, TObjectPtr<ISynchronizedObjectBase>> m_synchronizedObjects{};
    TArray<TObjectPtr<ISynchronizedObjectBase>> m_objectsArray{};

    const int MAX_BATCH_SIZE = 8192;

public:
    // NetworkManager methods

    void AddSynchronizedObject(ISynchronizedObjectBase& obj);
    void RemoveSynchronizedObject(ISynchronizedObjectBase& obj);
    void GetObjectsToSync(TArray<TTuple<TObjectPtr<ISynchronizedObjectBase>, int>>& outObjectsToSync);

    UFUNCTION(BlueprintCallable)
    void OnClientConnected(FString client);
    UFUNCTION(BlueprintCallable)
    void OnBytesRecieved(UPARAM(ref) TArray<uint8>& encodedObjects);
    UFUNCTION(BlueprintCallable)
    bool TryAcknoledge(UPARAM(ref) TArray<uint8>& recievedBytes, TArray<uint8>& outEncodedAck, FString& outIP);


    UFUNCTION(BlueprintCallable)
    bool TryEncodeObjects(TArray<UNetworkBatch*>& outNetworkBatches);

    UFUNCTION(BlueprintCallable)
    void EncodeObjects(TArray<uint8>& outEncodedObjects);
    UFUNCTION(BlueprintCallable)
    void DecodeObjects(UPARAM(ref) TArray<uint8>& encodedObjects);

    UFUNCTION(BlueprintCallable)
    int GetMaxBatchSize();
    UFUNCTION(BlueprintCallable)
    void TestMethod();


private:
    UNetworkManager(); 
};
