#include "Network/SpecializedProperties/FString/SynchronizedFStringList.h"

USynchronizedFStringList::USynchronizedFStringList()
{
}

USynchronizedFStringList::USynchronizedFStringList(TArray<FString> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<FString>(initialValue, m_value);
}

void USynchronizedFStringList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<FString>();
}

int USynchronizedFStringList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FString>(m_value);
}

void USynchronizedFStringList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FString>(m_value, buffer, offset, forSync);
}

void USynchronizedFStringList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FString>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFStringList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<FString>(m_value, m_previousValue);
}

