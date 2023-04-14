#include "Network/SpecializedProperties/FVector3f/SynchronizedFVector3fList.h"

USynchronizedFVector3fList::USynchronizedFVector3fList()
{
}

USynchronizedFVector3fList::USynchronizedFVector3fList(TArray<FVector3f> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<FVector3f>(initialValue, m_value);
}

void USynchronizedFVector3fList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<FVector3f>();
}

int USynchronizedFVector3fList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FVector3f>(m_value);
}

void USynchronizedFVector3fList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FVector3f>(m_value, buffer, offset, forSync);
}

void USynchronizedFVector3fList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FVector3f>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFVector3fList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<FVector3f>(m_value, m_previousValue);
}

