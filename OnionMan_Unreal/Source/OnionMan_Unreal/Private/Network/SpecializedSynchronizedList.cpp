#include "Network/SpecializedSynchronizedList.h"

USpecializedSynchronizedList::USpecializedSynchronizedList()
{
}

USpecializedSynchronizedList::USpecializedSynchronizedList(uint16 propertyID)
{
    m_propertyID = propertyID;
}

bool USpecializedSynchronizedList::NeedSync()
{
    CheckNeedSync();
    return m_needSync;
}

const uint16 USpecializedSynchronizedList::PropertyID() const
{
    return m_propertyID;
}

void USpecializedSynchronizedList::Init()
{
}

int USpecializedSynchronizedList::GetEncodedPropertySize()
{
    return 0;
}

void USpecializedSynchronizedList::PutEncodedPropertyToBuffer(TArray<uint8> &buffer, int &offset, bool forSync)
{
}

void USpecializedSynchronizedList::DecodeProperty(TArray<uint8> &encodedProperty, int &offset, int propertySize)
{
}

void USpecializedSynchronizedList::CheckNeedSync()
{
}
