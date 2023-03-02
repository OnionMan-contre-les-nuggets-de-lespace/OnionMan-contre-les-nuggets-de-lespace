#include "Network/SpecializedProperties/FVector2f/SynchronizedFVector2f.h"

USynchronizedFVector2f::USynchronizedFVector2f()
{
}

USynchronizedFVector2f::USynchronizedFVector2f(FVector2f value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFVector2f::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<FVector2f>();
}

int USynchronizedFVector2f::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FVector2f>(m_value);
}

void USynchronizedFVector2f::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FVector2f>(m_value, buffer, offset, forSync);
}

void USynchronizedFVector2f::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FVector2f>(m_value, encodedProperty, offset, propertySize);
}

