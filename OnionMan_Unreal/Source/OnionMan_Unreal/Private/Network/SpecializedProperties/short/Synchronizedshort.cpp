#include "Network/SpecializedProperties/short/Synchronizedshort.h"

USynchronizedshort::USynchronizedshort()
{
}

USynchronizedshort::USynchronizedshort(short value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedshort::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<short>();
}

int USynchronizedshort::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<short>(m_value);
}

void USynchronizedshort::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<short>(m_value, buffer, offset, forSync);
}

void USynchronizedshort::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<short>(m_value, encodedProperty, offset, propertySize);
}

