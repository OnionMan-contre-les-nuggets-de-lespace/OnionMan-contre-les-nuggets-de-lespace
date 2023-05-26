#include "Network/SpecializedProperties/double/SynchronizedDouble.h"

USynchronizedDouble::USynchronizedDouble()
{
}

USynchronizedDouble::USynchronizedDouble(double value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedDouble::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<double>();
}

int USynchronizedDouble::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<double>(m_value);
}

void USynchronizedDouble::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<double>(m_value, buffer, offset, forSync);
}

void USynchronizedDouble::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<double>(m_value, encodedProperty, offset, propertySize);
}

