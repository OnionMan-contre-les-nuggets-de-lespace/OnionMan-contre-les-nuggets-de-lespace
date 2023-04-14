#include "Network/SpecializedProperties/FQuat4f/SynchronizedFQuat4f.h"

USynchronizedFQuat4f::USynchronizedFQuat4f()
{
}

USynchronizedFQuat4f::USynchronizedFQuat4f(FQuat4f value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFQuat4f::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<FQuat4f>();
}

int USynchronizedFQuat4f::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FQuat4f>(m_value);
}

void USynchronizedFQuat4f::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FQuat4f>(m_value, buffer, offset, forSync);
}

void USynchronizedFQuat4f::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FQuat4f>(m_value, encodedProperty, offset, propertySize);
}

