#include "Network/SpecializedProperties/double/SynchronizedDoubleList.h"

USynchronizedDoubleList::USynchronizedDoubleList()
{
}

USynchronizedDoubleList::USynchronizedDoubleList(TArray<double> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<double>(initialValue, m_value);
}

void USynchronizedDoubleList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<double>();
}

int USynchronizedDoubleList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<double>(m_value);
}

void USynchronizedDoubleList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<double>(m_value, buffer, offset, forSync);
}

void USynchronizedDoubleList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<double>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedDoubleList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<double>(m_value, m_previousValue);
}

