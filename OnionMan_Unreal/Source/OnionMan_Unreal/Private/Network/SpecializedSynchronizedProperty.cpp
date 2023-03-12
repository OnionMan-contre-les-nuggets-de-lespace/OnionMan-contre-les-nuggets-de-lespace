#include "Network/SpecializedSynchronizedProperty.h"

USpecializedSynchronizedProperty::USpecializedSynchronizedProperty()
{
}

USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(uint16 propertyID)
{
    m_propertyID = propertyID;
}

bool USpecializedSynchronizedProperty::NeedSync()
{
    return true;
    return m_needSync;
}

const uint16 USpecializedSynchronizedProperty::PropertyID() const
{
    return m_propertyID;
}

void USpecializedSynchronizedProperty::Init()
{
}

int USpecializedSynchronizedProperty::GetEncodedPropertySize()
{
    return 0;
}

void USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
}

void USpecializedSynchronizedProperty::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
}

