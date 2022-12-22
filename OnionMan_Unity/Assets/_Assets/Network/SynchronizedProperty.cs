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
            get { return m_value; }
            set
            {
                if (!m_value.Equals(value))
                {
                    m_value = value;
                    m_needSync = true;
                }
            }
        }

        public bool NeedSync 
        { 
            get => m_needSync; 
            set => m_needSync = value; 
        }

        public ushort PropertyID => m_propertyID;

        [SerializeField]
        private T m_value;
        [SerializeField]
        private ushort m_propertyID;

        [SerializeField] //Temp
        private bool m_needSync = false;

        private Action<T> m_onValueChanged;

        public SynchronizedProperty(T value)
        {
            m_value = value;
        }

        public IEnumerable<byte> EncodeProperty(bool forSync = true)
        {
            if (forSync)
            {
                m_needSync = false;
            }
            IEnumerable<byte> encodedProperty = EncodingUtility.Encode(m_propertyID).Concat(EncodingUtility.Encode(m_value));
            encodedProperty = EncodingUtility.Encode(encodedProperty.Count()).Concat(encodedProperty);
            Debug.LogWarning($"SyncProp<{typeof(T)}> Encoded Value : {EncodingUtility.GetBytesAsString(encodedProperty)}");
            return encodedProperty;
        }

        public void DecodeProperty(byte[] encodedProperty, ref int offset, int propertySize) 
        {
            T decodedValue = EncodingUtility.Decode<T>(encodedProperty, ref offset, propertySize);
            if (!m_value.Equals(decodedValue))
            {
                m_value = decodedValue;
                if (m_onValueChanged != null)
                {
                    m_onValueChanged(m_value);
                }
            }
            Debug.LogWarning($"SyncProp<{typeof(T)}> Decoded Value : {decodedValue}");
        }
    }
}
