// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkManager.h"
#include "Network/EncodingUtility.h"
#include "LogUtils.h"

using namespace OnionMan::Network;

UNetworkManager::UNetworkManager()
{
    LOG_ERROR("Creating NetworkManager")
}

void UNetworkManager::AddSynchronizedObject(ISynchronizedObjectBase& obj)
{
    uint32 objID = obj.ObjectID();
    if (m_synchronizedObjects.Contains(objID))
    {
        LOG_ERROR("The object ID %i is already used", objID);
        return;
    }
    m_synchronizedObjects.Add(objID, &obj);
    m_objectsArray.Add(&obj);
}

void UNetworkManager::RemoveSynchronizedObject(ISynchronizedObjectBase& obj)
{
    uint32 objID = obj.ObjectID();
    if (!m_synchronizedObjects.Contains(objID))
    {
        LOG_ERROR("No object with ID %i", objID);
        return;
    }
    m_synchronizedObjects.Remove(objID);
    m_objectsArray.Remove(&obj);
}

void UNetworkManager::GetObjectsToSync(TArray<TTuple<TObjectPtr<ISynchronizedObjectBase>, int>>& outObjectsToSync)
{
    outObjectsToSync.Empty();
    for (TObjectPtr<ISynchronizedObjectBase> synchronizedObject : m_objectsArray)
    {
        ObjectNeedSyncResult needSyncResult = synchronizedObject->NeedSync();
        if (needSyncResult.NeedSync())
        {
            outObjectsToSync.Add(TTuple<TObjectPtr<ISynchronizedObjectBase>, int>{synchronizedObject, needSyncResult.EncodedSize()});
        }
    }
}

void UNetworkManager::OnClientConnected(FString client)
{
    LOG_ERROR("New Client Connected, waw : %s", *client);
}

void UNetworkManager::OnBytesRecieved(UPARAM(ref) TArray<uint8>& encodedObjects)
{
    DecodeObjects(encodedObjects);
}

bool UNetworkManager::TryAcknoledge(UPARAM(ref) TArray<uint8>& recievedBytes, TArray<uint8>& outEncodedAck, FString& outIP)
{
    int offset = 0;
    outIP = EncodingUtility::Decode<FString>(recievedBytes, offset, recievedBytes.Num());

    TArray<FString> ip{};
    outIP.ParseIntoArray(ip, TEXT("."));
    LOG_ERROR("Recieved IP : %s", *outIP);

    if (ip.Num() != 4) 
    {
        return false;
    }

    for (FString stringByte : ip)
    {
        if (stringByte.IsNumeric())
        {
            int byte = FCString::Atoi(*stringByte);
            if (0 > byte || 255 < byte) 
            {
                return false;
            }
        }
        else 
        {
            return false;
        }
    }

    offset = 0;
    outEncodedAck.SetNumUninitialized(EncodingUtility::GetSizeOf<FString>(&AcknoledgeMessage));
    EncodingUtility::PutEncodedValueInBuffer<FString>(AcknoledgeMessage, outEncodedAck, offset);
    return true;
}

bool UNetworkManager::TryEncodeObjects(TArray<UNetworkBatch*>& outNetworkBatches)
{
    TArray<TTuple<TObjectPtr<ISynchronizedObjectBase>, int>> objectsToSync{};
    GetObjectsToSync(objectsToSync);

    if (objectsToSync.Num() == 0) 
    {
        outNetworkBatches = TArray<UNetworkBatch*>{};
        return false;
    }
    LOG_ERROR("%i objectsToSyncs : id : %i", objectsToSync.Num(), objectsToSync[0].Key->ObjectID())

    TArray<BatchInfos*> encodedObjectsBatches = TArray<BatchInfos*>();
    encodedObjectsBatches.Add(new BatchInfos(TArray<TObjectPtr<ISynchronizedObjectBase>>(), 0));
    int currentBatchIndex = 0;

    for(TTuple<TObjectPtr<ISynchronizedObjectBase>, int> object : objectsToSync)
    {
        BatchInfos* currentBatckInfos = encodedObjectsBatches[currentBatchIndex];
        if (currentBatckInfos->BatchSize + object.Value > MAX_BATCH_SIZE)
        {
            BatchInfos* newBatch = new BatchInfos(TArray<TObjectPtr<ISynchronizedObjectBase>>(), 0);
            newBatch->BatchSize = object.Value;
            newBatch->ObjectsToSync.Add(object.Key);
            encodedObjectsBatches.Add(newBatch);

            currentBatchIndex++;
        }
        else
        {
            currentBatckInfos->BatchSize += object.Value;
            currentBatckInfos->ObjectsToSync.Add(object.Key);
        }
    }

    outNetworkBatches = TArray<UNetworkBatch*>{};
    for(BatchInfos* batch : encodedObjectsBatches)
    {
        TArray<uint8> encodedObjectsBuffer = TArray<uint8>{};
        encodedObjectsBuffer.SetNumUninitialized(batch->BatchSize);
        int offset = 0;

        for (TObjectPtr<ISynchronizedObjectBase> synchronizedObject : batch->ObjectsToSync)
        {
            synchronizedObject->PutEncodedObjectToBuffer(encodedObjectsBuffer, offset, true);
        }

        UNetworkBatch* a = NewObject<UNetworkBatch>();
        a->EncodedBatch = encodedObjectsBuffer;
        outNetworkBatches.Add(a);

        delete batch;
    }

    return true;
}

void UNetworkManager::EncodeObjects(TArray<uint8>& outEncodedObjects)
{
    TArray<TTuple<TObjectPtr<ISynchronizedObjectBase>, int>> objectsToSync{};
    GetObjectsToSync(objectsToSync);

    int encodedObjectsTotalSize = 0;
    for (TTuple<TObjectPtr<ISynchronizedObjectBase>, int> obj : objectsToSync)
    {
        encodedObjectsTotalSize += obj.Value;
    }

    LOG_ERROR("Encoded Size = %i", encodedObjectsTotalSize);

    outEncodedObjects.Empty();
    outEncodedObjects.SetNumUninitialized(encodedObjectsTotalSize);
    int offset = 0;

    for (TTuple<TObjectPtr<ISynchronizedObjectBase>, int> obj : objectsToSync)
    {
        LOG_ERROR("Encoding object %i at offset %i", obj.Key->ObjectID(), offset);
        obj.Key->PutEncodedObjectToBuffer(outEncodedObjects, offset);
    }
}

void UNetworkManager::DecodeObjects(UPARAM(ref) TArray<uint8>& encodedObjects)
{
    int offset = 0;
    int bufferSize = encodedObjects.Num();
    while (offset < bufferSize)
    {
        int objectSize = EncodingUtility::Decode<int>(encodedObjects, offset);
        int initialOffset = offset;

        uint32 objectID = EncodingUtility::Decode<uint32>(encodedObjects, offset);
        int objectDataSize = objectSize - sizeof(uint32);

        if (m_synchronizedObjects.Contains(objectID))
        {
            TObjectPtr<ISynchronizedObjectBase> synchronizedObject = m_synchronizedObjects[objectID];
            synchronizedObject->DecodeObject(encodedObjects, offset, objectDataSize);
            if (offset - initialOffset != objectSize)
            {
                LOG_ERROR("Offset Overflow !")
            }
        }
        else
        {
            LOG_ERROR("There are no object with ID %i", objectID);
        }
    }
}

int UNetworkManager::GetMaxBatchSize()
{
    return MAX_BATCH_SIZE;
}

void UNetworkManager::TestMethod()
{
    /*TArray<TArray<int>&> testArray = TArray<TArray<int>&>{};

    for (int d = 0; d < 10; d++) 
    {
        TArray<int> dArray = TArray<int>{};

        for (int i = 0; i < 10; i++)
        {
            dArray.Add(d * 10 + i);
        }
        testArray.Add(dArray);
    }

    LOG_ERROR("Array of Array COUNT : %i", testArray.Num());
    for (int i = 0; i < testArray.Num(); i++) 
    {
        LOG_WARNING("Sub array %i : Count : %i", i, testArray[i].Num())
            
        for (int j = 0; j < testArray[i].Num(); j++)
        {
            LOG_WARNING("element at %i : Value : %i", j, testArray[i][j])

        }

    }*/
}
