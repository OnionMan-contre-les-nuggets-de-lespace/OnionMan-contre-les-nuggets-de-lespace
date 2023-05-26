#include "Network/SpecializedProperties/TYPENAME/SynchronizedCLASSNAMEList.h"

USynchronizedCLASSNAMEList::USynchronizedCLASSNAMEList()
{
}

USynchronizedCLASSNAMEList::USynchronizedCLASSNAMEList(TArray<TYPENAME> &initialValue, uint16 propertyID) : 
    USpecializedSynchronizedList::USpecializedSynchronizedList(propertyID)
{
    CopyTo<TYPENAME>(initialValue, m_value);
}

void USynchronizedCLASSNAMEList::Init()
{
    USpecializedSynchronizedList::Init();
    InitGeneric<TYPENAME>();
}

int USynchronizedCLASSNAMEList::GetEncodedPropertySize()
{
    USpecializedSynchronizedList::GetEncodedPropertySize();
    return GetEncodedPropertySizeGeneric<TYPENAME>(m_value);
}

void USynchronizedCLASSNAMEList::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    USpecializedSynchronizedList::PutEncodedPropertyToBuffer(buffer, offset, forSync);
    PutEncodedPropertyToBufferGeneric<TYPENAME>(m_value, buffer, offset, forSync);
}

void USynchronizedCLASSNAMEList::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    USpecializedSynchronizedList::DecodeProperty(encodedProperty, offset, propertySize);
    DecodePropertyGeneric<TYPENAME>(m_value, m_previousValue, encodedProperty, offset, propertySize);
}

void USynchronizedCLASSNAMEList::CheckNeedSync()
{
    USpecializedSynchronizedList::CheckNeedSync();
    CheckNeedSyncGeneric<TYPENAME>(m_value, m_previousValue);
}