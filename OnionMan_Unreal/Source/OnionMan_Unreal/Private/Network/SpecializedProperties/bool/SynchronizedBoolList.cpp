#include "Network/SpecializedProperties/bool/SynchronizedBoolList.h"

USynchronizedBoolList::USynchronizedBoolList()
{
}

USynchronizedBoolList::USynchronizedBoolList(TArray<bool> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<bool>(initialValue, m_value);
}

void USynchronizedBoolList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<bool>();
}

int USynchronizedBoolList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<bool>(m_value);
}

void USynchronizedBoolList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<bool>(m_value, buffer, offset, forSync);
}

void USynchronizedBoolList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<bool>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedBoolList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<bool>(m_value, m_previousValue);
}

