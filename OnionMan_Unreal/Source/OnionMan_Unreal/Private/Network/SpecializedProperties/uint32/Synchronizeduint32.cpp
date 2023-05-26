#include "Network/SpecializedProperties/uint32/SynchronizedUint32.h"

USynchronizedUint32::USynchronizedUint32()
{
}

USynchronizedUint32::USynchronizedUint32(uint32 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedUint32::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<uint32>();
}

int USynchronizedUint32::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint32>(m_value);
}

void USynchronizedUint32::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint32>(m_value, buffer, offset, forSync);
}

void USynchronizedUint32::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint32>(m_value, encodedProperty, offset, propertySize);
}

