#include "Network/SpecializedProperties/TCHAR/SynchronizedTCHAR.h"

USynchronizedTCHAR::USynchronizedTCHAR()
{
}

USynchronizedTCHAR::USynchronizedTCHAR(TCHAR value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedTCHAR::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<TCHAR>();
}

int USynchronizedTCHAR::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TCHAR>(m_value);
}

void USynchronizedTCHAR::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TCHAR>(m_value, buffer, offset, forSync);
}

void USynchronizedTCHAR::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TCHAR>(m_value, encodedProperty, offset, propertySize);
}

