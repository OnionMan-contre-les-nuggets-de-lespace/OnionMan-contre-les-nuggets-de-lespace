#include "Network/SpecializedProperties/int/SynchronizedIntList.h"

USynchronizedIntList::USynchronizedIntList()
{
}

USynchronizedIntList::USynchronizedIntList(TArray<int> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<int>(initialValue, m_value);
}

void USynchronizedIntList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<int>();
}

int USynchronizedIntList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int>(m_value);
}

void USynchronizedIntList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int>(m_value, buffer, offset, forSync);
}

void USynchronizedIntList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedIntList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<int>(m_value, m_previousValue);
}

