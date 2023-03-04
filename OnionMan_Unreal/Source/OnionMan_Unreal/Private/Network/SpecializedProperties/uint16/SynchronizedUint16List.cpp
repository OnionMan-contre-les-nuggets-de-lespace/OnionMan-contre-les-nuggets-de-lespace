#include "Network/SpecializedProperties/uint16/SynchronizedUint16List.h"

USynchronizedUint16List::USynchronizedUint16List()
{
}

USynchronizedUint16List::USynchronizedUint16List(TArray<uint16> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<uint16>(initialValue, m_value);
}

void USynchronizedUint16List::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<uint16>();
}

int USynchronizedUint16List::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint16>(m_value);
}

void USynchronizedUint16List::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint16>(m_value, buffer, offset, forSync);
}

void USynchronizedUint16List::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint16>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedUint16List::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<uint16>(m_value, m_previousValue);
}

