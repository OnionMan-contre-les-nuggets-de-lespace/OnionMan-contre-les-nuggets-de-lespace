#include "Network/SpecializedProperties/int/Synchronizedint.h"

USynchronizedint::USynchronizedint()
{
}

USynchronizedint::USynchronizedint(int value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedint::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<int>();
}

int USynchronizedint::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int>(m_value);
}

void USynchronizedint::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int>(m_value, buffer, offset, forSync);
}

void USynchronizedint::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int>(m_value, encodedProperty, offset, propertySize);
}

