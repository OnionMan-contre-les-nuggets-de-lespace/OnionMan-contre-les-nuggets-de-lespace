using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEngine;

namespace OnionMan.Network
{
    public abstract class SynchronizedMonoBehaviour : MonoBehaviour, ISynchronizedObject
    {
        #region ISynchronizedObject Implementation
        public uint ObjectID { get => m_objectID; }

        public Dictionary<ushort, ISynchronizedProperty> Properties 
        { 
            get => m_synchronizedProperties;
        }

        [SerializeField]
        private uint m_objectID;

        private Dictionary<ushort, ISynchronizedProperty> m_synchronizedProperties = new Dictionary<ushort, ISynchronizedProperty>();
        private int m_encodedPropertiesSize;

        public ObjectNeedSyncResult NeedSync()
        {
            m_encodedPropertiesSize = 0;
            foreach (ISynchronizedProperty property in GetPropertiesToSync())
            {
                m_encodedPropertiesSize += property.GetEncodedPropertySize();
            }
            return new ObjectNeedSyncResult(enabled && m_encodedPropertiesSize > 0, sizeof(int) + sizeof(uint) + m_encodedPropertiesSize); // Size + ID + EncodedProperties
        }

        public void PutEncodedObjectToBuffer(byte[] buffer, ref int offset, bool forSync = true)
        {
            EncodingUtility.PutEncodedValueInBuffer(m_encodedPropertiesSize + sizeof(uint), buffer, ref offset); // Put Size
            EncodingUtility.PutEncodedValueInBuffer(m_objectID, buffer, ref offset);                             // Put ID

            foreach (ISynchronizedProperty property in GetPropertiesToSync())
            {
                property.PutEncodedPoropertyToBuffer(buffer, ref offset, forSync);                               // Put all Properties
            }
        }
        public IEnumerable<byte> EncodeObject(bool forSync = true)
        {
            IEnumerable<byte> encodedObject = EncodingUtility.Encode(m_objectID);
            foreach (ISynchronizedProperty property in GetPropertiesToSync())
            {
                encodedObject = encodedObject.Concat(property.EncodeProperty(forSync));
            }

            return EncodingUtility.Encode(encodedObject.Count()).Concat(encodedObject);
        }

        public void DecodeObject(byte[] encodedProperties, ref int offset, int size)
        {
            int objectStartOffset = offset;
            while (offset < size + objectStartOffset)
            {
                int propertySize = EncodingUtility.Decode<int>(encodedProperties, ref offset);
                int porpertyStartOffset = offset;

                ushort propertyID = EncodingUtility.Decode<ushort>(encodedProperties, ref offset);
                int dataSize = propertySize - sizeof(ushort);

                if (m_synchronizedProperties.TryGetValue(propertyID, out ISynchronizedProperty synchronizedProperty))
                {
                    synchronizedProperty.DecodeProperty(encodedProperties, ref offset, dataSize);
                    if (offset - porpertyStartOffset != propertySize)
                    {
                        Debug.LogError("Offset Overflow !");
                    }
                }
                else
                {
                    throw new InvalidDataException($"There are no object with ID {propertyID}");
                }
            }
        }

        public abstract void LoadProperties();

        private void ResetNeedSync(bool state)
        {
            foreach(ISynchronizedProperty prop in m_synchronizedProperties.Values) 
            {
                prop.NeedSync = state;
            }
        }

        public IEnumerable<ISynchronizedProperty> GetPropertiesToSync()
        {
            return m_synchronizedProperties.Values.Where((ISynchronizedProperty prop) => prop.NeedSync);
        }

        public void AddSynchronizedProperty(ISynchronizedProperty synchronizedProperty)
        {
            synchronizedProperty.Init();

            ushort propID = synchronizedProperty.PropertyID;
            if (m_synchronizedProperties.ContainsKey(propID))
            {
                throw new InvalidDataException($"The ID {propID} is already used by {m_synchronizedProperties[propID]}");
            }
            m_synchronizedProperties.Add(propID, synchronizedProperty);
        }

        public void RemoveSynchronizedProperty(ISynchronizedProperty synchronizedProperty)
        {
            ushort propID = synchronizedProperty.PropertyID;
            if (!m_synchronizedProperties.ContainsKey(propID))
            {
                throw new InvalidDataException($"No properties with ID {propID} in the Object {m_objectID}");
            }
            m_synchronizedProperties.Remove(propID);
        }
        #endregion

        // Start is called before the first frame update
        protected virtual void Start()
        {
            LoadProperties();
            NetworkManager.Instance.AddSynchronizedObject(this);
        }

        protected virtual void OnDestroy()
        {
            NetworkManager.Instance.RemoveSynchronizedObject(this);
        }
    }
}
