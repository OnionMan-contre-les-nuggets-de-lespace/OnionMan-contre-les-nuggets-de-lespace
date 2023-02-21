#include "Network/SpecializedProperties/uint16/Synchronizeduint16.h"

USynchronizeduint16::USynchronizeduint16()
{
}

USynchronizeduint16::USynchronizeduint16(uint16 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizeduint16::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<uint16>();
}

int USynchronizeduint16::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint16>(m_value);
}

void USynchronizeduint16::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint16>(m_value, buffer, offset, forSync);
}

void USynchronizeduint16::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint16>(m_value, encodedProperty, offset, propertySize);
}

