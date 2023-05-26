#include "Network/SpecializedProperties/int64/SynchronizedInt64List.h"

USynchronizedInt64List::USynchronizedInt64List()
{
}

USynchronizedInt64List::USynchronizedInt64List(TArray<int64> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<int64>(initialValue, m_value);
}

void USynchronizedInt64List::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<int64>();
}

int USynchronizedInt64List::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int64>(m_value);
}

void USynchronizedInt64List::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int64>(m_value, buffer, offset, forSync);
}

void USynchronizedInt64List::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int64>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedInt64List::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<int64>(m_value, m_previousValue);
}

