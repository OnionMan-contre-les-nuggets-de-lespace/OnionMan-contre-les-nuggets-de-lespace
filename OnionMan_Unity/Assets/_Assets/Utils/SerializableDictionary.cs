using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;

[Serializable]
public class SerializableDictionary<TKey, TValue> : ISerializationCallbackReceiver
{
    [Serializable]
    private struct KeyValuePair
    {
        [SerializeField]
        private TKey m_key;
        [SerializeField]
        private TValue m_value;

        public TKey Key => m_key; 

        public TValue Value { get => m_value; set => m_value = value; }

        public KeyValuePair(TKey key, TValue value)
        {
            m_key = key;
            m_value = value;
        }
    }

    [SerializeField]
    private List<KeyValuePair> m_keyValuePairs = new List<KeyValuePair>();

    Dictionary<TKey, TValue> m_dictionary = new Dictionary<TKey, TValue>();

    public int Count => m_dictionary.Count;

    

    public void Add(TKey key, TValue value)
    {
        m_keyValuePairs.Add(new KeyValuePair (key, value));
        m_dictionary.Add(key, value);
    }

    public TValue this[TKey key]
    {
        get
        {
            return m_dictionary[key];
        }
        set
        {
            m_dictionary[key] = value;
        }
    }

    #region Utils
    private KeyValuePair GetPairWithKey(TKey key)
    {
        var result = m_keyValuePairs.Where((KeyValuePair pair) => pair.Key.Equals(key));
        if (!result.Any()) 
        {
            throw new KeyNotFoundException();
        }
        return result.First();
    }

    public void OnBeforeSerialize()
    {
        m_keyValuePairs.Clear();
        foreach (TKey key in m_dictionary.Keys)
        {
            m_keyValuePairs.Add(new KeyValuePair(key, m_dictionary[key]));
        }
    }

    public void OnAfterDeserialize()
    {
        foreach (KeyValuePair pair in m_keyValuePairs)
        {
            m_dictionary[pair.Key] = pair.Value;
        }
    }
    #endregion
}
