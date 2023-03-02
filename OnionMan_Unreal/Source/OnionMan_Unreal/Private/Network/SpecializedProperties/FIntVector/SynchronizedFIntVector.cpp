#include "Network/SpecializedProperties/FIntVector/SynchronizedFIntVector.h"

USynchronizedFIntVector::USynchronizedFIntVector()
{
}

USynchronizedFIntVector::USynchronizedFIntVector(FIntVector value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedFIntVector::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<FIntVector>();
}

int USynchronizedFIntVector::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FIntVector>(m_value);
}

void USynchronizedFIntVector::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FIntVector>(m_value, buffer, offset, forSync);
}

void USynchronizedFIntVector::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FIntVector>(m_value, encodedProperty, offset, propertySize);
}

