#include "Network/SpecializedProperties/uint16/SynchronizedUint16.h"

USynchronizedUint16::USynchronizedUint16()
{
}

USynchronizedUint16::USynchronizedUint16(uint16 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedUint16::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<uint16>();
}

int USynchronizedUint16::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint16>(m_value);
}

void USynchronizedUint16::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint16>(m_value, buffer, offset, forSync);
}

void USynchronizedUint16::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint16>(m_value, encodedProperty, offset, propertySize);
}

