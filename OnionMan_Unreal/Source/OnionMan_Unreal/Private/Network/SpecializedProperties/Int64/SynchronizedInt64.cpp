#include "Network/SpecializedProperties/int64/SynchronizedInt64.h"

USynchronizedInt64::USynchronizedInt64()
{
}

USynchronizedInt64::USynchronizedInt64(int64 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedInt64::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<int64>();
}

int USynchronizedInt64::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int64>(m_value);
}

void USynchronizedInt64::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int64>(m_value, buffer, offset, forSync);
}

void USynchronizedInt64::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int64>(m_value, encodedProperty, offset, propertySize);
}

