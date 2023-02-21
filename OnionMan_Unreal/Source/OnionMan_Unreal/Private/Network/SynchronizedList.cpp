// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SynchronizedList.h"
#include "Network/EncodingUtility.h"

using namespace OnionMan::Network;

template<typename T>
void USynchronizedList<T>::CheckNeedSync()
{
    if (m_needSync)
    {
        return;
    }

    if (ListEquals(m_value, m_previousValue))
    {
        m_needSync = false;
        return;
    }

    m_sizeMayHaveChanged = true;
    m_previousValue = Copy(m_value);
    m_needSync = true;
}

template <typename T>
USynchronizedList<T>::~USynchronizedList()
{

}

template <typename T>
bool USynchronizedList<T>:: NeedSync()
{
    CheckNeedSync();
    return m_needSync;
}

template <typename T>
const uint16 USynchronizedList<T>::PropertyID() const
{
    return m_propertyID;
}

template <typename T>
void USynchronizedList<T>::Init()
{
    m_hasTAFixedSize = EncodingUtility::HasFixedEncodedSize<T>();
    if (m_hasTAFixedSize)
    {
        m_fixedTSize = EncodingUtility::GetSizeOf<T>();
    }
    else
    {
        m_sizeMayHaveChanged = true;
    }
}

template <typename T>
int USynchronizedList<T>::GetEncodedPropertySize()
{
    if (m_hasTAFixedSize)
    {
        int encodedTSize = sizeof(int) + m_fixedTSize; // Size + Data
        return sizeof(int) + sizeof(uint16) + encodedTSize * m_value.Count; // Size + ID + Each element Size * n
    }

    if (m_sizeMayHaveChanged)
    {
        m_sizeMayHaveChanged = false;
        m_encodedSize = sizeof(int) + sizeof(uint16); // Property size + PropertyID
        for (T element : m_value) 
        {
            m_encodedSize += sizeof(int) + GetTSize(element); // each element size + Data
        }
    }
    return m_encodedSize;
}

template <typename T>
void USynchronizedList<T>::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync)
{
    if (forSync)
    {
        m_needSync = false;
    }

    EncodingUtility::PutEncodedValueInBuffer(GetEncodedPropertySize() - sizeof(int), buffer, offset);   // Put Size
    EncodingUtility::PutEncodedValueInBuffer(m_propertyID, buffer, offset);                             // Put ID
    for (T item : m_value)                                                                              // For each element in list :
    {
        EncodingUtility::PutEncodedValueInBuffer(GetTSize(item), buffer, offset);                       // Put Size
        EncodingUtility::PutEncodedValueInBuffer(item, buffer, offset);                                 // Put Data
    }
}

template <typename T>
void USynchronizedList<T>::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{
    int propertyStartOffset = offset;
    TArray<T> decodedList {};

    while (offset < propertyStartOffset + propertySize) 
    {
        int itemSize = EncodingUtility::Decode<int>(encodedProperty, offset);
        decodedList.Add(EncodingUtility::Decode<T>(encodedProperty, offset, itemSize));
    }

    if (!ListEquals(m_value, decodedList))
    {
        CopyTo(decodedList, result);
        CopyTo(decodedList, m_previousValue);
        // if (m_onValueChanged != null)
        // {
        //     m_onValueChanged(m_value);
        // }
    }
}
