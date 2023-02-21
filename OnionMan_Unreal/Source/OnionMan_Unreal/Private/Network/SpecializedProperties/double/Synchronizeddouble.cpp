#include "Network/SpecializedProperties/double/Synchronizeddouble.h"

USynchronizeddouble::USynchronizeddouble()
{
}

USynchronizeddouble::USynchronizeddouble(double value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizeddouble::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<double>();
}

int USynchronizeddouble::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<double>(m_value);
}

void USynchronizeddouble::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<double>(m_value, buffer, offset, forSync);
}

void USynchronizeddouble::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<double>(m_value, encodedProperty, offset, propertySize);
}

