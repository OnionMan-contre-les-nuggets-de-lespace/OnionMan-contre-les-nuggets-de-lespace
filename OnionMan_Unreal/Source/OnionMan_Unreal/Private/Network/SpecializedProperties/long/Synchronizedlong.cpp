#include "Network/SpecializedProperties/long/Synchronizedlong.h"

USynchronizedlong::USynchronizedlong()
{
}

USynchronizedlong::USynchronizedlong(long value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedlong::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<long>();
}

int USynchronizedlong::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<long>(m_value);
}

void USynchronizedlong::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<long>(m_value, buffer, offset, forSync);
}

void USynchronizedlong::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<long>(m_value, encodedProperty, offset, propertySize);
}

