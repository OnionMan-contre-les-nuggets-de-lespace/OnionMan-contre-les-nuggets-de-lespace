// Fill out your copyright notice in the Description page of Project Settings.


#include "USynchronizedProperty.h"

template <typename T>
USynchronizedProperty<T>::USynchronizedProperty(T value, uint16 propertyID)
{
    m_propertyID = propertyID;
    m_value = value;
}
template <typename T>
USynchronizedProperty<T>::~USynchronizedProperty(){

}

template <typename T>
bool USynchronizedProperty<T>::NeedSync() override
{
    return m_needSync;
}

template <typename T>
uint16 USynchronizedProperty<T>::PropertyID() override
{
    return m_propertyID;
}

template <typename T>
T USynchronizedProperty<T>::Value()
{
    return m_value;
}

template <typename T>
void USynchronizedProperty<T>::Init() override
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
int USynchronizedProperty<T>::GetEncodedPropertySize() override
{
    if (m_hasFixedSize)
    {
        return sizeof(int) + sizeof(uint16) + m_fixedSize; // Size + ID + Data
    }

    if (m_sizeMayHaveChanged)
    {
        m_sizeMayHaveChanged = false;
        m_encodedSize = sizeof(int) + sizeof(uint16) + EncodingUtility::GetSizeOf<T>(m_value); // Size + ID + Data
    }
    return m_encodedSize;
}

template <typename T>
void USynchronizedProperty<T>::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true) override
{
    if (forSync)
    {
        m_needSync = false;
    }

    EncodingUtility::PutEncodedValueInBuffer<int>(GetEncodedPropertySize() - sizeof(int), buffer, offset); // Put Size
    EncodingUtility::PutEncodedValueInBuffer<uint16>(m_propertyID, buffer, offset);                        // Put ID
    EncodingUtility::PutEncodedValueInBuffer<T>(m_value, buffer, offset);                                  // Put Data
}

template <typename T>
TArray<uint8> USynchronizedProperty<T>::EncodeProperty<T>(bool forSync = true) override
{
    if (forSync)
    {
        m_needSync = false;
    }
    TArray<uint8> encodedProperty;
    encodedProperty.Reserve(GetEncodedPropertySize());
    encodedProperty.Append(EncodingUtility::Encode<int>(GetEncodedPropertySize() - sizeof(int)));
    encodedProperty.Append(EncodingUtility::Encode<uint16>(m_propertyID));
    encodedProperty.Append(EncodingUtility::Encode<T>(m_value));
    return encodedProperty;
}

template <typename T>
void USynchronizedProperty<T>::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize) override
{
    T decodedValue = EncodingUtility::Decode<T>(encodedProperty, offset, propertySize);
    if (!m_value.Equals(decodedValue))
    {
        m_value = decodedValue;
        // if (m_onValueChanged != null)
        // {
        //     m_onValueChanged(m_value);
        // }
    }
}
