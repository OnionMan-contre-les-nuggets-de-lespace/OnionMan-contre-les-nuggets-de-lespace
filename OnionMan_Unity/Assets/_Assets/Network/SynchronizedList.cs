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

        private List<T> m_previousValue = new List<T>();

        private Action<List<T>> m_onValueChanged;

        public SynchronizedList(List<T> initialValue, ushort propertyID)
        {
            m_value = DeepCopy(initialValue);
            m_propertyID = propertyID; 
            m_previousValue = new List<T>();
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
            Debug.LogWarning($"SyncList<{typeof(T)}> Encoded Value : {EncodingUtility.GetBytesAsString(encodedList)}");
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
                m_value = DeepCopy(decodedList);
                m_previousValue = DeepCopy(decodedList);
                if (m_onValueChanged != null)
                {
                    m_onValueChanged(m_value);
                }
            }

            Debug.LogWarning($"SyncList<{typeof(T)}> Decoded Value : {decodedList}");
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

        private static List<T> DeepCopy(List<T> listToCopy)
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

            m_previousValue = DeepCopy(m_value);
            m_needSync = true;
        }
    }
}
