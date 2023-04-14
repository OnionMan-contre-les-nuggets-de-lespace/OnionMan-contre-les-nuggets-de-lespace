#include "Network/SpecializedProperties/int16/SynchronizedInt16.h"

USynchronizedInt16::USynchronizedInt16()
{
}

USynchronizedInt16::USynchronizedInt16(int16 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedInt16::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<int16>();
}

int USynchronizedInt16::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int16>(m_value);
}

void USynchronizedInt16::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int16>(m_value, buffer, offset, forSync);
}

void USynchronizedInt16::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int16>(m_value, encodedProperty, offset, propertySize);
}

