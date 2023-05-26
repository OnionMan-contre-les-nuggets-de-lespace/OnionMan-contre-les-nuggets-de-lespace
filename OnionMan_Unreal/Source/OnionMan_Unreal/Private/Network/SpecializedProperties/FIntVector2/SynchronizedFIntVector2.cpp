#include "Network/SpecializedProperties/FIntVector2/SynchronizedFIntVector2.h"

USynchronizedFIntVector2::USynchronizedFIntVector2()
{
}

USynchronizedFIntVector2::USynchronizedFIntVector2(FIntVector2 value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFIntVector2::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<FIntVector2>();
}

int USynchronizedFIntVector2::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FIntVector2>(m_value);
}

void USynchronizedFIntVector2::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FIntVector2>(m_value, buffer, offset, forSync);
}

void USynchronizedFIntVector2::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FIntVector2>(m_value, encodedProperty, offset, propertySize);
}

