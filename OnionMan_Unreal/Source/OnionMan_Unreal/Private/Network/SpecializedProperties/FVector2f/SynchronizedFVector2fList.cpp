#include "Network/SpecializedProperties/FVector2f/SynchronizedFVector2fList.h"

USynchronizedFVector2fList::USynchronizedFVector2fList()
{
}

USynchronizedFVector2fList::USynchronizedFVector2fList(TArray<FVector2f> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<FVector2f>(initialValue, m_value);
}

void USynchronizedFVector2fList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<FVector2f>();
}

int USynchronizedFVector2fList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FVector2f>(m_value);
}

void USynchronizedFVector2fList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FVector2f>(m_value, buffer, offset, forSync);
}

void USynchronizedFVector2fList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FVector2f>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFVector2fList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<FVector2f>(m_value, m_previousValue);
}

