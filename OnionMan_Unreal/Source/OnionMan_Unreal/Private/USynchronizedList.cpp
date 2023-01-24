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

template <typename T>
USynchronizedList<T>::USynchronizedList(TArray<T> initialValue, uint16 propertyID)
{

}

template <typename T>
USynchronizedList<T>::~USynchronizedList()
{

}

template <typename T>
bool USynchronizedList<T>:: NeedSync()
{

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
void USynchronizedList<T>::SetValue(T value)
{

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
void USynchronizedList<T>::PutEncodedPropertyToBuffer(TArray<uint8>& buffer, int& offset, bool forSync = true)
{

}

template <typename T>
TArray<uint8> USynchronizedList<T>::EncodeProperty(bool forSync = true)
{

}

template <typename T>
void USynchronizedList<T>::DecodeProperty(TArray<uint8>& encodedProperty, int& offset, int propertySize)
{

}
