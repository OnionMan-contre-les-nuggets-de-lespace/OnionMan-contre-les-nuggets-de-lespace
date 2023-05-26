#include "Network/SpecializedProperties/uint32/SynchronizedUint32List.h"

USynchronizedUint32List::USynchronizedUint32List()
{
}

USynchronizedUint32List::USynchronizedUint32List(TArray<uint32> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<uint32>(initialValue, m_value);
}

void USynchronizedUint32List::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<uint32>();
}

int USynchronizedUint32List::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint32>(m_value);
}

void USynchronizedUint32List::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint32>(m_value, buffer, offset, forSync);
}

void USynchronizedUint32List::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint32>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedUint32List::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<uint32>(m_value, m_previousValue);
}

