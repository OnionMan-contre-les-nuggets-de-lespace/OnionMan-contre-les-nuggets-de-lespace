// Fill out your copyright notice in the Description page of Project Settings.


#include "USynchronizedList.h"
#include "EncodingUtility.h"

using namespace OnionMan::Network;

template<typename T>
int USynchronizedList<T>::GetTSize(T element)
{
    if (m_hasTAFixedSize)
    {
        return m_fixedTSize;
    }
    return EncodingUtility::GetSizeOf<T>(element);
}

template<typename T>
static bool USynchronizedList<T>::ListEquals(TArray<T> self, TArray<T> other)
{
    if (self == nullptr || other == nullptr)
    {
        return false;
    }

    if (other.Num() != self.Num())
    {
        return false;
    }

    for (int i = 0; i < self.Count; i++)
    {
        if (self[i] != other[i])
        {
            return false;
        }
    }

    return true;
}

template<typename T>
TArray<T> USynchronizedList<T>::Copy(TArray<T> listToCopy)
{
    if (listToCopy == nullptr)
    {
        return nullptr;
    }
    TArray<T> copy{};
    copy.Reserve(listToCopy.GetAllocatedSize());

    for(T item : listToCopy)
    {
        copy.Add(item);
    }
    return copy;
}

void CheckNeedSync()
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
USynchronizedList<T>::USynchronizedList(TArray<T> initialValue, uint16 propertyID)
{
    m_value = Copy(initialValue);
    m_propertyID = propertyID;
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
const TArray<T>& USynchronizedList<T>::GetValue() const
{
    return m_value;
}

template <typename T>
void USynchronizedList<T>::SetValue(TArray<T> value)
{
    m_value = value;
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
            m_encodedSize += sizeof(int) + GetTSize(element);
        }
        m_value.ForEach((T element) = > ); // each element size + Data
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

    EncodingUtility::PutEncodedValueInBuffer(GetEncodedPropertySize() - sizeof(int), buffer, offset); // Put Size
    EncodingUtility::PutEncodedValueInBuffer(m_propertyID, buffer, offset);                           // Put ID
    for (T item : m_value)                                                                            // For each element in list :
    {
        EncodingUtility::PutEncodedValueInBuffer(GetTSize(item), buffer, offset);                     // Put Size
        EncodingUtility::PutEncodedValueInBuffer(item, buffer, offset);                               // Put Data
    }
}

template <typename T>
const TArray<uint8>& USynchronizedList<T>::EncodeProperty(bool forSync = true)
{
    if (forSync)
    {
        m_needSync = false;
    }

    int propertySize = GetEncodedPropertySize();
    int offset = 0;
    TArray<uint8> encodedList{}
    encodedList.Reserve(propertySize);
    EncodingUtility::PutEncodedValueInBuffer(propertySize, encodedList, offset);
    EncodingUtility::PutEncodedValueInBuffer(m_propertyID, encodedList, offset);

    for (T item : m_value)
    {
        EncodingUtility::PutEncodedValueInBuffer(GetTSize(item), encodedList, offset);
        EncodingUtility::PutEncodedValueInBuffer(item, encodedList, offset);
    }
    return encodedList;
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
        m_value = Copy(decodedList);
        m_previousValue = Copy(decodedList);
        // if (m_onValueChanged != null)
        // {
        //     m_onValueChanged(m_value);
        // }
    }
}
