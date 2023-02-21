#include "Network/SpecializedProperties/bool/Synchronizedbool.h"

USynchronizedbool::USynchronizedbool()
{
}

USynchronizedbool::USynchronizedbool(bool value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedbool::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<bool>();
}

int USynchronizedbool::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<bool>(m_value);
}

void USynchronizedbool::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<bool>(m_value, buffer, offset, forSync);
}

void USynchronizedbool::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<bool>(m_value, encodedProperty, offset, propertySize);
}

