using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace OnionMan.Network
{
    [Serializable]
    public class SynchronizedList<T> : List<T>, ISynchronizedProperty
    {
        public bool NeedSync
        {
            get => m_needSync;
            set => m_needSync = value;
        }

        public ushort PropertyID => m_propertyID;

        [SerializeField]
        private ushort m_propertyID;

        [SerializeField] //Temp
        private bool m_needSync = false;

        private Action<List<T>> m_onValueChanged;

        public SynchronizedList(List<T> initialValue, ushort propertyID)
        {
            SetThisValue(initialValue);
            m_propertyID = propertyID;
        }

        public IEnumerable<byte> EncodeProperty(bool forSync = true)
        {
            if (forSync)
            {
                m_needSync = false;
            }

            IEnumerable<byte> encodedList = EncodingUtility.Encode(m_propertyID);
            foreach (T value in this)
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

            if (!ListEquals(this, decodedList))
            {
                SetThisValue(decodedList);
                if (m_onValueChanged != null)
                {
                    m_onValueChanged(decodedList);
                }
            }

            Debug.LogWarning($"SyncList<{typeof(T)}> Decoded Value : {decodedList}");
        }

        private static bool ListEquals(List<T> self, List<T> other)
        {
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

        private void SetThisValue(List<T> values)
        {
            this.Clear();
            foreach (T value in values)
            {
                this.Add(value);
            }
        }

    }
}
