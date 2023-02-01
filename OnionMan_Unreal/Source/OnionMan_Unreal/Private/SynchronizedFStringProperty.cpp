// Fill out your copyright notice in the Description page of Project Settings.


#include "SynchronizedFStringProperty.h"
#include "EncodingUtility.h"

using namespace OnionMan::Network;

USynchronizedFStringProperty::USynchronizedFStringProperty()
{
}
USynchronizedFStringProperty::USynchronizedFStringProperty(FString value, uint16 propertyID)
{
	m_value = value;
	m_propertyID = propertyID;
}

USynchronizedFStringProperty::~USynchronizedFStringProperty()
{
}

bool USynchronizedFStringProperty::NeedSync()
{
	return m_needSync;
}

const uint16 USynchronizedFStringProperty::PropertyID() const
{
	return m_propertyID;
}

void USynchronizedFStringProperty::Init()
{
    m_hasFixedSize = EncodingUtility::HasFixedEncodedSize<FString>();
    if (m_hasFixedSize)
    {
        m_fixedSize = EncodingUtility::GetSizeOf<FString>();
    }
    else
    {
        m_sizeMayHaveChanged = true;
    }
}

int USynchronizedFStringProperty::GetEncodedPropertySize()
{
    if (m_hasFixedSize)
    {
        return sizeof(int) + sizeof(uint16) + m_fixedSize; // Size + ID + Data
    }

    if (m_sizeMayHaveChanged)
    {
        m_sizeMayHaveChanged = false;
        m_encodedSize = sizeof(int) + sizeof(uint16) + EncodingUtility::GetSizeOf<FString>(&m_value); // Size + ID + Data
    }
    return m_encodedSize;
}

void USynchronizedFStringProperty::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    if (forSync)
    {
        m_needSync = false;
    }

    EncodingUtility::PutEncodedValueInBuffer<int>(GetEncodedPropertySize() - sizeof(int), buffer, offset); // Put Size
    EncodingUtility::PutEncodedValueInBuffer<uint16>(m_propertyID, buffer, offset);                        // Put ID
    EncodingUtility::PutEncodedValueInBuffer<FString>(m_value, buffer, offset);                                  // Put Data
}

void USynchronizedFStringProperty::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    FString decodedValue = EncodingUtility::Decode<FString>(encodedProperty, offset, propertySize);
    if (m_value != decodedValue)
    {
        m_value = decodedValue;
        // if (m_onValueChanged != null)
        // {
        //     m_onValueChanged(m_value);
        // }
    }
}
