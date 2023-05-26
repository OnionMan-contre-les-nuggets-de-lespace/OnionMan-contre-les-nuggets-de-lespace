using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

namespace OnionMan.Utils
{
    /// <summary>
    /// Empty interface used to draw the custom PropertyDrawer for any SerializedDictionary class
    /// </summary>
    public interface ISerializedDictionaryPair { }

    /// <summary>
    /// Use this class to create a dictionary that can be serialized by Unity
    /// It also features a custom PropertyDrawer
    /// Do not use this class directly
    /// Example:
    /// 	[Serializable] public class MyDict : SerializedDictionary<string, GameObject> { }
    ///		[SerializeField] private MyDict m_myDict;
    /// </summary>
    [Serializable]
    public class SerializedDictionary<TKey, TValue> : IDictionary<TKey, TValue>
    {
        /// <summary>
        /// Data structure to serialize the dictionary
        /// </summary>
        [Serializable]
        public class Pair : ISerializedDictionaryPair
        {
            [SerializeField] public TKey Key;
            [SerializeField] public TValue Value;
        }

        [SerializeField] private List<Pair> m_pairs = new List<Pair>();


        #region IDictionary
        public ICollection<TKey> Keys => m_pairs.Select(pair => pair.Key).ToArray();

        public ICollection<TValue> Values => m_pairs.Select(pair => pair.Value).ToArray();

        public int Count => m_pairs.Count;

        public bool IsReadOnly => false;

        public TValue this[TKey key]
        {
            get
            {
                int index = m_pairs.FindIndex(pair => pair.Key.Equals(key));
                if (index < 0)
                {
                    throw new KeyNotFoundException();
                }
                else
                {
                    return m_pairs[index].Value;
                }
            }
            set
            {
                int index = m_pairs.FindIndex(pair => pair.Key.Equals(key));
                if (index < 0)
                {
                    m_pairs.Add(new Pair { Key = key, Value = value });
                }
                else
                {
                    m_pairs[index] = new Pair { Key = m_pairs[index].Key, Value = value };
                }
            }
        }

        public void Add(TKey key, TValue value)
        {
            if (!ContainsKey(key))
            {
                m_pairs.Add(new Pair { Key = key, Value = value });
            }
        }

        public bool ContainsKey(TKey key)
        {
            return m_pairs.FindIndex(pair => pair.Key.Equals(key)) > -1;
        }

        public bool Remove(TKey key)
        {
            int index = m_pairs.FindIndex(pair => pair.Key.Equals(key));
            if (index < 0)
            {
                return false;
            }
            else
            {
                m_pairs.RemoveAt(index);
                return true;
            }
        }

        public bool TryGetValue(TKey key, out TValue value)
        {
            int index = m_pairs.FindIndex(pair => pair.Key.Equals(key));
            if (index < 0)
            {
                value = default(TValue);
                return false;
            }
            else
            {
                value = m_pairs[index].Value;
                return true;
            }
        }

        public void Add(KeyValuePair<TKey, TValue> item)
        {
            Add(item.Key, item.Value);
        }

        public void Clear()
        {
            m_pairs.Clear();
        }

        public bool Contains(KeyValuePair<TKey, TValue> item)
        {
            int index = m_pairs.FindIndex(pair => pair.Key.Equals(item.Key));
            if (index < 0)
            {
                return false;
            }
            else
            {
                return m_pairs[index].Value.Equals(item.Value);
            }
        }

        public void CopyTo(KeyValuePair<TKey, TValue>[] array, int arrayIndex)
        {
            for (int i = 0; i < m_pairs.Count; i++)
            {
                array[i + arrayIndex] = new KeyValuePair<TKey, TValue>(m_pairs[i].Key, m_pairs[i].Value);
            }
        }

        public bool Remove(KeyValuePair<TKey, TValue> item)
        {
            if (Contains(item))
            {
                return Remove(item.Key);
            }
            else
            {
                return false;
            }
        }

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            foreach (var item in m_pairs)
            {
                yield return new KeyValuePair<TKey, TValue>(item.Key, item.Value);
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return m_pairs.GetEnumerator();
        }

        #endregion
    }
}