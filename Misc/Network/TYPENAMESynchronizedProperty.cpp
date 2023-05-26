#include "Network/SpecializedProperties/TYPENAME/SynchronizedCLASSNAME.h"

USynchronizedCLASSNAME::USynchronizedCLASSNAME()
{
}

USynchronizedCLASSNAME::USynchronizedCLASSNAME(TYPENAME value, uint16 propertyID) : 
    USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(propertyID)
{
    m_value = value;
}

void USynchronizedCLASSNAME::Init()
{
    USpecializedSynchronizedProperty::Init();
    InitGeneric<TYPENAME>();
}

int USynchronizedCLASSNAME::GetEncodedPropertySize()
{
    USpecializedSynchronizedProperty::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TYPENAME>(m_value);
}

void USynchronizedCLASSNAME::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TYPENAME>(m_value, buffer, offset, forSync);
}

void USynchronizedCLASSNAME::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedProperty::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TYPENAME>(m_value, encodedProperty, offset, propertySize);
}