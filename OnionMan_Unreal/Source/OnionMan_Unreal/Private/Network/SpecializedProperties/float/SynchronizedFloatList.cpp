#include "Network/SpecializedProperties/float/SynchronizedFloatList.h"

USynchronizedFloatList::USynchronizedFloatList()
{
}

USynchronizedFloatList::USynchronizedFloatList(TArray<float> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<float>(initialValue, m_value);
}

void USynchronizedFloatList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<float>();
}

int USynchronizedFloatList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<float>(m_value);
}

void USynchronizedFloatList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<float>(m_value, buffer, offset, forSync);
}

void USynchronizedFloatList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<float>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFloatList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<float>(m_value, m_previousValue);
}

