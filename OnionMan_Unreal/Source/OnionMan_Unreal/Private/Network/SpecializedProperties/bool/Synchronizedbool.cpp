#include "Network/SpecializedProperties/bool/SynchronizedBool.h"

USynchronizedBool::USynchronizedBool()
{
}

USynchronizedBool::USynchronizedBool(bool value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedBool::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<bool>();
}

int USynchronizedBool::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<bool>(m_value);
}

void USynchronizedBool::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<bool>(m_value, buffer, offset, forSync);
}

void USynchronizedBool::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<bool>(m_value, encodedProperty, offset, propertySize);
}

