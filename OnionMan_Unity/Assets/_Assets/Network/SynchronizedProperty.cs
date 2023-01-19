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

        public Action<T> OnValueChanged 
        { 
            get => m_onValueChanged;
            set => m_onValueChanged = value;
        }

		[SerializeField]
        private T m_value;
        [SerializeField]
        private ushort m_propertyID;

        [SerializeField] //Temp
        private bool m_needSync = false;

        private bool m_hasFixedSize = false;
        private int m_fixedSize = 0;

        private Action<T> m_onValueChanged;

		public SynchronizedProperty(T value, ushort ID)
        {
            m_value = value;
            m_propertyID = ID;

            m_hasFixedSize = EncodingUtility.HasFixedEncodedSize<T>();
            if (m_hasFixedSize)
			{
                m_fixedSize = EncodingUtility.GetEncodedSize<T>();
			}
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

		public int GetEncodedPropertySize()
		{
			if (m_hasFixedSize)
			{
                return m_fixedSize;
			}
            return EncodingUtility.GetEncodedSize(m_value);
		}
	}
}
