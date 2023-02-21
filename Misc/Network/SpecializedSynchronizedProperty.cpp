#include "SpecializedSynchronizedProperty.h"

USpecializedSynchronizedProperty::USpecializedSynchronizedProperty()
{
}

USpecializedSynchronizedProperty::USpecializedSynchronizedProperty(uint16 propertyID)
{
    m_propertyID = propertyID;
}

bool USpecializedSynchronizedProperty::NeedSync()
{
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

void USpecializedSynchronizedProperty::PutEncodedPropertyToBuffer(TArray<uint8> &buffer, int &offset, bool forSync)
{
}

void USpecializedSynchronizedProperty::DecodeProperty(TArray<uint8> &encodedProperty, int &offset, int propertySize)
{
}

template <typename T>
void USpecializedSynchronizedProperty::InitGeneric()
{
    m_hasFixedSize = EncodingUtility::HasFixedEncodedSize<T>();
    if (m_hasFixedSize)
    {
        m_fixedSize = EncodingUtility::GetSizeOf<T>();
    }
    else
    {
        m_sizeMayHaveChanged = true;
    }
}

template <typename T>
inline int USpecializedSynchronizedProperty::GetEncodedPropertySizeGeneric(T& value)
{
    if (m_hasFixedSize)
    {
        return sizeof(int) + sizeof(uint16) + m_fixedSize; // Size + ID + Data
    }

    if (m_sizeMayHaveChanged)
    {
        m_sizeMayHaveChanged = false;
        m_encodedSize = sizeof(int) + sizeof(uint16) + EncodingUtility::GetSizeOf<T>(&value); // Size + ID + Data
    }
    return m_encodedSize;
}

template <typename T>
void USpecializedSynchronizedProperty::PutEncodedPropertyToBufferGeneric(T &propertyValue, TArray<uint8> &buffer, int &offset, bool forSync)
{
    if (forSync)
    {
        m_needSync = false;
    }

    EncodingUtility::PutEncodedValueInBuffer<int>(GetEncodedPropertySize() - sizeof(int), buffer, offset); // Put Size
    EncodingUtility::PutEncodedValueInBuffer<uint16>(m_propertyID, buffer, offset);                        // Put ID
    EncodingUtility::PutEncodedValueInBuffer<T>(propertyValue, buffer, offset); 
}

template <typename T>
void USpecializedSynchronizedProperty::DecodePropertyGeneric(T &outValue, TArray<uint8> &encodedProperty, int &offset, int propertySize)
{
    T decodedValue = EncodingUtility::Decode<T>(encodedProperty, offset, propertySize);
    if (outValue != decodedValue)
    {
        outValue = decodedValue;
        // if (m_onValueChanged != null)
        // {
        //     m_onValueChanged(m_value);
        // }
    }
}
