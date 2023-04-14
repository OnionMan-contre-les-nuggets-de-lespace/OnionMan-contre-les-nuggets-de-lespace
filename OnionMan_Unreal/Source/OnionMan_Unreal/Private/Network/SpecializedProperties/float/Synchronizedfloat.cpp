#include "Network/SpecializedProperties/float/SynchronizedFloat.h"

USynchronizedFloat::USynchronizedFloat()
{
}

USynchronizedFloat::USynchronizedFloat(float value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFloat::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<float>();
}

int USynchronizedFloat::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<float>(m_value);
}

void USynchronizedFloat::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<float>(m_value, buffer, offset, forSync);
}

void USynchronizedFloat::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<float>(m_value, encodedProperty, offset, propertySize);
}

