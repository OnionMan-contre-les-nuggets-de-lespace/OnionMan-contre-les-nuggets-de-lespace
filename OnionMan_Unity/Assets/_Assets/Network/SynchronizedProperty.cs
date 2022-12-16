using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    [System.Serializable]
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
            return EncodingUtility.Encode<T>(m_value);
        }
    }
}
