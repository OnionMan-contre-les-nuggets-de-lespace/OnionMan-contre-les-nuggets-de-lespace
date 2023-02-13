// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkManager.h"
#include "Network/EncodingUtility.h"
#include "LogUtils.h"

using namespace OnionMan::Network;

UNetworkManager::UNetworkManager()
{
}

// Dans le fichier source
UNetworkManager& UNetworkManager::Instance()
{
    static UNetworkManager s_instance{};
    return s_instance;
}

void UNetworkManager::AddSynchronizedObject(ISynchronizedObjectBase& obj)
{
	uint32 objID = obj.ObjectID();
	if (m_synchronizedObjects.Contains(objID))
	{
		LOG_ERROR("The object ID %i is already used", objID);
	}
	m_synchronizedObjects.Add(objID, &obj);
	m_objectsArray.Add(&obj);
}

void UNetworkManager::GetObjectsToSync(TArray<TTuple<ISynchronizedObjectBase*, int>>& outObjectsToSync)
{
    outObjectsToSync.Empty();
    for (ISynchronizedObjectBase* synchronizedObject : m_objectsArray)
    {
        ObjectNeedSyncResult needSyncResult = synchronizedObject->NeedSync();
        if (needSyncResult.NeedSync())
        {
            outObjectsToSync.Add(TTuple<ISynchronizedObjectBase*, int>{synchronizedObject, needSyncResult.EncodedSize()});
        }
    }
}

void UNetworkManager::EncodeObjects(TArray<uint8>& outEncodedObjects)
{
    TArray<TTuple<ISynchronizedObjectBase*, int>> objectsToSync{};
    GetObjectsToSync(objectsToSync);

    int encodedObjectsTotalSize = 0;
    for(TTuple<ISynchronizedObjectBase*, int> obj : objectsToSync)
    {
        encodedObjectsTotalSize += obj.Value;
    }

    outEncodedObjects.Empty();
    outEncodedObjects.SetNumUninitialized(encodedObjectsTotalSize);
    int offset = 0;

    for(TTuple<ISynchronizedObjectBase*, int> obj : objectsToSync)
    {
        obj.Key->PutEncodedObjectToBuffer(outEncodedObjects, offset);
    }
}

void UNetworkManager::DecodeObjects(TArray<uint8>& encodedObjects)
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
            ISynchronizedObjectBase* synchronizedObject = m_synchronizedObjects[objectID];
            synchronizedObject->DecodeObject(encodedObjects, offset, objectDataSize);
            if (offset - initialOffset != objectSize)
            {
                LOG_ERROR("Offset Overflow !")
            }
        }
        else
        {
            LOG_ERROR("There are no object with ID", objectID);
        }
    }
}
