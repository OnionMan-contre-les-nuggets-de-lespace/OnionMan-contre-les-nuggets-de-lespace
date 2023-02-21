#include "Network/SpecializedProperties/uint64/Synchronizeduint64.h"

USynchronizeduint64::USynchronizeduint64()
{
}

USynchronizeduint64::USynchronizeduint64(uint64 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizeduint64::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<uint64>();
}

int USynchronizeduint64::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<uint64>(m_value);
}

void USynchronizeduint64::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<uint64>(m_value, buffer, offset, forSync);
}

void USynchronizeduint64::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<uint64>(m_value, encodedProperty, offset, propertySize);
}

