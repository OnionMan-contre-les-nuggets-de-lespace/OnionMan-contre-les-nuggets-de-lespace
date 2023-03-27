using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace OnionMan.Network
{
    [Serializable]
    public class SynchronizedProperty<T> : ISynchronizedProperty
    {
        public T Value
        {
            get
            {
                if (Role == NetworkRole.Sender)
                {
                    Debug.LogError("You should not try to get the value of a sender property");
                }
                return m_value;
            }
            set
            {
                if (Role == NetworkRole.Reciever)
                {
                    Debug.LogError("Do not set the value of a reciever property");
                    return;
                }
                if (!m_value.Equals(value))
                {
                    m_value = value;
                    m_needSync = true;

                    m_sizeMayHaveChanged = true;
                }
            }
        }

        public bool NeedSync
        {
            get 
            {
                if (Role == NetworkRole.Reciever)
                {
                    return false;
                }

                return m_needSync;
            }
            set => m_needSync = value;
        }

        public ushort PropertyID => m_propertyID;

        public NetworkRole Role { get => m_role; }

        public Action<T> OnValueChanged 
        { 
            get => m_onValueChanged;
            set => m_onValueChanged = value;
        }

        [SerializeField]
        private NetworkRole m_role = NetworkRole.SenderAndReciever;

        [SerializeField]
        private T m_value;
        [SerializeField]
        private ushort m_propertyID;

        [SerializeField] // @TODO Supprimer �a
        private bool m_needSync = false;

        private bool m_hasFixedSize = false;
        private int m_fixedSize = 0;

        private Action<T> m_onValueChanged;
        private bool m_sizeMayHaveChanged;
        private int m_encodedSize;

        public SynchronizedProperty(T value, ushort ID)
        {
            m_value = value;
            m_propertyID = ID;
            Init();
        }

        public void Init()
        {
            m_hasFixedSize = EncodingUtility.HasFixedEncodedSize<T>();
            if (m_hasFixedSize)
            {
                m_fixedSize = EncodingUtility.GetSizeOf<T>();
            }
            else
            {
                m_sizeMayHaveChanged = true;
            }
        }

        public void PutEncodedPropertyToBuffer(byte[] buffer, ref int offset, bool forSync = true)
        {
            if (forSync)
            {
                if (Role == NetworkRole.Reciever)
                {
                    Debug.LogError("Do not try to encode a reciever property");
                    return;
                }
                m_needSync = false;
            }

            EncodingUtility.PutEncodedValueInBuffer(GetEncodedPropertySize() - sizeof(int), buffer, ref offset); // Put Size
            EncodingUtility.PutEncodedValueInBuffer(m_propertyID, buffer, ref offset);                           // Put ID
            EncodingUtility.PutEncodedValueInBuffer(m_value, buffer, ref offset);                                // Put Data
        }

        public IEnumerable<byte> EncodeProperty(bool forSync = true)
        {
            if (forSync)
            {
                if (Role == NetworkRole.Reciever)
                {
                    Debug.LogError("Do not try to encode a reciever property");
                    return new byte[0];
                }

                m_needSync = false;
            }
            byte[] encodedProperty = new byte[GetEncodedPropertySize()];
            int offset = 0;
            EncodingUtility.PutEncodedValueInBuffer(GetEncodedPropertySize() - sizeof(int), encodedProperty, ref offset); // Put Size
            EncodingUtility.PutEncodedValueInBuffer(m_propertyID, encodedProperty, ref offset);                           // Put ID
            EncodingUtility.PutEncodedValueInBuffer(m_value, encodedProperty, ref offset);                                // Put Data

            return encodedProperty;
        }

        public void DecodeProperty(byte[] encodedProperty, ref int offset, int propertySize) 
        {
            T decodedValue = EncodingUtility.Decode<T>(encodedProperty, ref offset, propertySize);

            if (Role == NetworkRole.Sender)
            {
                Debug.LogError("Do not try to decode a sender property");
                return;
            }

            if (!m_value.Equals(decodedValue))
            {
                m_value = decodedValue;
                m_sizeMayHaveChanged = true;
                if (m_onValueChanged != null)
                {
                    m_onValueChanged(m_value);
                }
            }
        }

        public int GetEncodedPropertySize()
        {
            if (m_hasFixedSize)
            {
                return sizeof(int) + sizeof(ushort) + m_fixedSize; // Size + ID + Data
            }

            if (m_sizeMayHaveChanged)
            {
                m_sizeMayHaveChanged = false;
                m_encodedSize = sizeof(int) + sizeof(ushort) + EncodingUtility.GetSizeOf(m_value); // Size + ID + Data
            }
            return m_encodedSize;
        }
    }
}
