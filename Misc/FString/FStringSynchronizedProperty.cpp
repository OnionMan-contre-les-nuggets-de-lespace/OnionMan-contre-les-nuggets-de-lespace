#include "Network/SpecializedProperties/FString/FStringSynchronizedProperty.h"

USynchronizedFString::USynchronizedFString()
{
}

USynchronizedFString::USynchronizedFString(FString value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFString::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<FString>();
}

int USynchronizedFString::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FString>(m_value);
}

void USynchronizedFString::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FString>(m_value, buffer, offset, forSync);
}

void USynchronizedFString::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FString>(m_value, encodedProperty, offset, propertySize);
}

