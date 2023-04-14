#include "Network/SpecializedProperties/int16/SynchronizedInt16List.h"

USynchronizedInt16List::USynchronizedInt16List()
{
}

USynchronizedInt16List::USynchronizedInt16List(TArray<int16> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<int16>(initialValue, m_value);
}

void USynchronizedInt16List::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<int16>();
}

int USynchronizedInt16List::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int16>(m_value);
}

void USynchronizedInt16List::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int16>(m_value, buffer, offset, forSync);
}

void USynchronizedInt16List::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int16>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedInt16List::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<int16>(m_value, m_previousValue);
}

