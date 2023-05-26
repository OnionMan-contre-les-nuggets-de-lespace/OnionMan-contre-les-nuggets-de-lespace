#include "Network/SpecializedProperties/int/SynchronizedInt.h"

USynchronizedInt::USynchronizedInt()
{
}

USynchronizedInt::USynchronizedInt(int value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedInt::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<int>();
}

int USynchronizedInt::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<int>(m_value);
}

void USynchronizedInt::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<int>(m_value, buffer, offset, forSync);
}

void USynchronizedInt::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<int>(m_value, encodedProperty, offset, propertySize);
}

