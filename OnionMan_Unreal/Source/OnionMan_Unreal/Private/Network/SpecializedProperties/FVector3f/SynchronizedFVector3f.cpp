#include "Network/SpecializedProperties/FVector3f/SynchronizedFVector3f.h"

USynchronizedFVector3f::USynchronizedFVector3f()
{
}

USynchronizedFVector3f::USynchronizedFVector3f(FVector3f value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFVector3f::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<FVector3f>();
}

int USynchronizedFVector3f::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FVector3f>(m_value);
}

void USynchronizedFVector3f::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FVector3f>(m_value, buffer, offset, forSync);
}

void USynchronizedFVector3f::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FVector3f>(m_value, encodedProperty, offset, propertySize);
}

