using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace OnionMan.Network
{
    [Serializable]
    public class SynchronizedList<T> : ISynchronizedProperty
    {
        public ushort PropertyID => m_propertyID;

        public bool NeedSync
        {
            get 
            {
                CheckNeedSync();
                return m_needSync;
            }
            set => m_needSync = value;
        }

        public List<T> Value
        {
            get => m_value; 
            set => m_value = value;
        }

        public Action<List<T>> OnValueChanged 
        { 
            get => m_onValueChanged; 
            set => m_onValueChanged = value; 
        }

        [SerializeField]
        private ushort m_propertyID;

        [SerializeField] //Temp
        private bool m_needSync = false;

        [SerializeField]
        private List<T> m_value = new List<T>();

        private bool m_hasTAFixedSize = false;
        private int m_fixedTSize = 0;

        private List<T> m_previousValue = new List<T>();
        private bool m_sizeMayHaveChanged = true;
        private int m_encodedSize;

        private Action<List<T>> m_onValueChanged;

		public SynchronizedList(List<T> initialValue, ushort propertyID)
        {
            m_value = Copy(initialValue);
            m_propertyID = propertyID; 
            m_previousValue = new List<T>();

            Init();
        }

        public void Init()
        {
            m_hasTAFixedSize = EncodingUtility.HasFixedEncodedSize<T>();
            if (m_hasTAFixedSize)
            {
                m_fixedTSize = EncodingUtility.GetSizeOf<T>();
            }
            else
            {
                m_sizeMayHaveChanged = true;
            }
        }

        public int GetEncodedPropertySize()
        {
            if (m_hasTAFixedSize)
            {
                int encodedTSize = sizeof(int) + m_fixedTSize; // Size + Data
                return sizeof(int) + sizeof(ushort) + encodedTSize * m_value.Count; // Size + ID + Each element Size * n
            }

            if (m_sizeMayHaveChanged)
            {
                m_sizeMayHaveChanged = false;
                m_encodedSize = sizeof(int) + sizeof(ushort); // Property size + PropertyID
                m_value.ForEach((T element) => m_encodedSize += (sizeof(int) + GetTSize(element))); // each element size + Data
            }
            return m_encodedSize;
        }

        public void PutEncodedPoropertyToBuffer(byte[] buffer, ref int offset, bool forSync = true)
        {
            if (forSync)
            {
                m_needSync = false;
            }

            EncodingUtility.PutEncodedValueInBuffer(GetEncodedPropertySize() - sizeof(int), buffer, ref offset); // Put Size
            EncodingUtility.PutEncodedValueInBuffer(m_propertyID, buffer, ref offset);                           // Put ID
            foreach (T t in m_value)                                                                             // For each element in list :
            {
                EncodingUtility.PutEncodedValueInBuffer(GetTSize(t), buffer, ref offset);                        // Put Size
                EncodingUtility.PutEncodedValueInBuffer(t, buffer, ref offset);                                  // Put Data
            }
        }
        public IEnumerable<byte> EncodeProperty(bool forSync = true)
        {
            if (forSync)
            {
                m_needSync = false;
            }

            IEnumerable<byte> encodedList = EncodingUtility.Encode(m_propertyID);
            foreach (T value in m_value)
            {
                IEnumerable<byte> encodedValue = EncodingUtility.Encode(value);
                encodedList = 
                    encodedList
                    .Concat(EncodingUtility.Encode(encodedValue.Count()))
                    .Concat(encodedValue);
            }
            encodedList = EncodingUtility.Encode(encodedList.Count()).Concat(encodedList);
            return encodedList;
        }

        public void DecodeProperty(byte[] encodedProperty, ref int offset, int propertySize)
        {
            int propertyStartOffset = offset;
            List<T> decodedList = new List<T>();
            
            while (offset < propertyStartOffset + propertySize) 
            {
                int itemSize = EncodingUtility.Decode<int>(encodedProperty, ref offset);
                decodedList.Add(EncodingUtility.Decode<T>(encodedProperty, ref offset, itemSize));
            }

            if (!ListEquals(m_value, decodedList))
            {
                m_value = Copy(decodedList);
                m_previousValue = Copy(decodedList);
                if (m_onValueChanged != null)
                {
                    m_onValueChanged(m_value);
                }
            }
        }
        
		private void CheckNeedSync()
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

        #region Utils
        private int GetTSize(T element)
        {
            if (m_hasTAFixedSize)
            {
                return m_fixedTSize;
            }
            return EncodingUtility.GetSizeOf(element);
        }

        private static bool ListEquals(List<T> self, List<T> other)
        {
            if (self == null || other == null)
            {
                return false;
            }

            if (other.Count != self.Count)
            {
                return false;
            }

            for (int i = 0; i < self.Count; i++)
            {
                if (!self[i].Equals(other[i]))
                {
                    return false;
                }
            }

            return true;
        }

        private static List<T> Copy(List<T> listToCopy)
        {
            if (listToCopy == null)
            {
                return null;
            }
            List<T> copy = new List<T>();
            foreach (T item in listToCopy)
            {
                copy.Add(item);
            }
            return copy;
        }
        #endregion
    }
}
