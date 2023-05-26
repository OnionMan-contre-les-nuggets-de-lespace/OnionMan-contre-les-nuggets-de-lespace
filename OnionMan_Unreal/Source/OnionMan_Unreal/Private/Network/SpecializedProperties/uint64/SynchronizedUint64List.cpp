#include "Network/SpecializedProperties/uint64/SynchronizedUint64List.h"

USynchronizedUint64List::USynchronizedUint64List()
{
}

USynchronizedUint64List::USynchronizedUint64List(TArray<uint64> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<uint64>(initialValue, m_value);
}

void USynchronizedUint64List::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<uint64>();
}

int USynchronizedUint64List::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint64>(m_value);
}

void USynchronizedUint64List::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint64>(m_value, buffer, offset, forSync);
}

void USynchronizedUint64List::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint64>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedUint64List::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<uint64>(m_value, m_previousValue);
}

