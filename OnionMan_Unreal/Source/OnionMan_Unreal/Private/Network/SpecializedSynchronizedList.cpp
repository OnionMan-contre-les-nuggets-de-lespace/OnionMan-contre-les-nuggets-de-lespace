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
    if (Role() == ENetworkRole::Receiver)
    {
        return false;
    }

    return true; // @TODO Remove it
    CheckNeedSync();
    return m_needSync;
}

const uint16 USpecializedSynchronizedList::PropertyID() const
{
    return m_propertyID;
}

const ENetworkRole USpecializedSynchronizedList::Role() const
{
    return m_role;
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
