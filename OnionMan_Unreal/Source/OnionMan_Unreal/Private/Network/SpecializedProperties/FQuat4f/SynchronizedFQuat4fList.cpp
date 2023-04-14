#include "Network/SpecializedProperties/FQuat4f/SynchronizedFQuat4fList.h"

USynchronizedFQuat4fList::USynchronizedFQuat4fList()
{
}

USynchronizedFQuat4fList::USynchronizedFQuat4fList(TArray<FQuat4f> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<FQuat4f>(initialValue, m_value);
}

void USynchronizedFQuat4fList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<FQuat4f>();
}

int USynchronizedFQuat4fList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FQuat4f>(m_value);
}

void USynchronizedFQuat4fList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FQuat4f>(m_value, buffer, offset, forSync);
}

void USynchronizedFQuat4fList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FQuat4f>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFQuat4fList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<FQuat4f>(m_value, m_previousValue);
}

