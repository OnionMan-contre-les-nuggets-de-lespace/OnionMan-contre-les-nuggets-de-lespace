#include "Network/SpecializedProperties/float/Synchronizedfloat.h"

USynchronizedfloat::USynchronizedfloat()
{
}

USynchronizedfloat::USynchronizedfloat(float value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedfloat::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<float>();
}

int USynchronizedfloat::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<float>(m_value);
}

void USynchronizedfloat::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<float>(m_value, buffer, offset, forSync);
}

void USynchronizedfloat::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<float>(m_value, encodedProperty, offset, propertySize);
}

