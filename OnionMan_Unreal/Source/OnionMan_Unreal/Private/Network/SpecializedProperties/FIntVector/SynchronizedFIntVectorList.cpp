#include "Network/SpecializedProperties/FIntVector/SynchronizedFIntVectorList.h"

USynchronizedFIntVectorList::USynchronizedFIntVectorList()
{
}

USynchronizedFIntVectorList::USynchronizedFIntVectorList(TArray<FIntVector> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<FIntVector>(initialValue, m_value);
}

void USynchronizedFIntVectorList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<FIntVector>();
}

int USynchronizedFIntVectorList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<FIntVector>(m_value);
}

void USynchronizedFIntVectorList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<FIntVector>(m_value, buffer, offset, forSync);
}

void USynchronizedFIntVectorList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<FIntVector>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedFIntVectorList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<FIntVector>(m_value, m_previousValue);
}

