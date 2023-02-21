#include "Network/SpecializedProperties/TYPENAME/TYPENAMESynchronizedProperty.h"

UTYPENAMESynchronizedProperty::UTYPENAMESynchronizedProperty()
{
}

UTYPENAMESynchronizedProperty::UTYPENAMESynchronizedProperty(TYPENAME value, uint16 propertyID) : USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void UTYPENAMESynchronizedProperty::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<TYPENAME>();
}

int UTYPENAMESynchronizedProperty::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TYPENAME>(m_value);
}

void UTYPENAMESynchronizedProperty::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TYPENAME>(m_value, buffer, offset, forSync);
}

void UTYPENAMESynchronizedProperty::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TYPENAME>(m_value, encodedProperty, offset, propertySize);
}
