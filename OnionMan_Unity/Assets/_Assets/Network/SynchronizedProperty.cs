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

        public byte[] Encode()
        {
            byte[] encodedProperty = EncodingUtility.Encode(m_value);
            return EncodingUtility.Encode(encodedProperty.Length).Concat(encodedProperty).ToArray();
        }

        public T Decode(byte[] encodedProperty, ref int offset) 
        {
            int propertySize = EncodingUtility.Decode<int>(encodedProperty, ref offset);
            return EncodingUtility.Decode<T>(encodedProperty, ref offset, propertySize);
        }
    }
}
