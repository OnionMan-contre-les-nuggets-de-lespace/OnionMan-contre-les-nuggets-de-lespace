using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace OnionMan.Network
{
    [Serializable]
    public class SynchronizedProperty<T>
    {
        public T Value
        {
            get { return m_value; }
            set
            {
                if (!m_value.Equals(value))
                {
                    m_value = value;
                    m_onValueChanged.Invoke(m_value);
                }
            }
        }

        [SerializeField] private T m_value;
        private Action<T> m_onValueChanged;

        public SynchronizedProperty(T value)
        {
            m_value = value;
        }

        public IEnumerable<byte> Encode()
        {
            IEnumerable<byte> encodedProperty = EncodingUtility.Encode(m_value);
            encodedProperty = EncodingUtility.Encode(encodedProperty.Count()).Concat(encodedProperty);
            Debug.LogWarning($"SyncProp<{typeof(T)}> Encoded Value : {EncodingUtility.GetBytesAsString(encodedProperty)}");
            return encodedProperty;
        }

        public T Decode(byte[] encodedProperty, ref int offset) 
        {
            int propertySize = EncodingUtility.Decode<int>(encodedProperty, ref offset);
            m_value = EncodingUtility.Decode<T>(encodedProperty, ref offset, propertySize);
            Debug.LogWarning($"SyncProp<{typeof(T)}> Decoded Value : {m_value}");
            return m_value;
        }
    }
}
