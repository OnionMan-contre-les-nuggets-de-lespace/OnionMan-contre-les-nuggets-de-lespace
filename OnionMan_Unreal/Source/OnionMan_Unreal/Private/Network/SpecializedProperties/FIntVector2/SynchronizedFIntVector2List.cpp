#include "Network/SpecializedProperties/FIntVector2/SynchronizedFIntVector2List.h"

USynchronizedFIntVector2List::USynchronizedFIntVector2List()
{
}

USynchronizedFIntVector2List::USynchronizedFIntVector2List(TArray<FIntVector2> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<FIntVector2>(initialValue, m_value);
}

void USynchronizedFIntVector2List::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<FIntVector2>();
}

int USynchronizedFIntVector2List::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FIntVector2>(m_value);
}

void USynchronizedFIntVector2List::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FIntVector2>(m_value, buffer, offset, forSync);
}

void USynchronizedFIntVector2List::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FIntVector2>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFIntVector2List::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<FIntVector2>(m_value, m_previousValue);
}

