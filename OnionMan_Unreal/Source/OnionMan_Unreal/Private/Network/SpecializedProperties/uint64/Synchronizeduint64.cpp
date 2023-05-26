#include "Network/SpecializedProperties/uint64/SynchronizedUint64.h"

USynchronizedUint64::USynchronizedUint64()
{
}

USynchronizedUint64::USynchronizedUint64(uint64 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedUint64::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<uint64>();
}

int USynchronizedUint64::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint64>(m_value);
}

void USynchronizedUint64::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint64>(m_value, buffer, offset, forSync);
}

void USynchronizedUint64::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint64>(m_value, encodedProperty, offset, propertySize);
}

