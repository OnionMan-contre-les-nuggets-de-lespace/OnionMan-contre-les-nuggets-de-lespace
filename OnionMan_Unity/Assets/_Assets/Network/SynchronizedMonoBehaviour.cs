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
        public uint ObjectID { get => m_ObjectID; }
        public bool NeedSync 
        { 
            get => AnyPropertyNeedSync();
        }
        public Dictionary<ushort, ISynchronizedProperty> Properties 
        { 
            get => m_synchronizedProperties;
        }

        [SerializeField]
        private uint m_ObjectID;

        private Dictionary<ushort, ISynchronizedProperty> m_synchronizedProperties = new Dictionary<ushort, ISynchronizedProperty>();

        public IEnumerable<byte> EncodeObject(bool forSync = true)
        {
            IEnumerable<byte> result = new byte[0];
            foreach (ISynchronizedProperty property in GetPropertiesToSync())
            {
                result = result.Concat(property.EncodeProperty(forSync));
            }
            return result;
        }

        public void DecodeObject(byte[] encodedProperties, ref int offset, int size)
        {
            while (offset < size)
            {
                int propertySize = EncodingUtility.Decode<int>(encodedProperties, ref offset);
                int initialOffset = offset;

                ushort propertyID = EncodingUtility.Decode<ushort>(encodedProperties, ref offset);
                int dataSize = propertySize - sizeof(ushort);

                if (m_synchronizedProperties.TryGetValue(propertyID, out ISynchronizedProperty synchronizedProperty))
                {
                    synchronizedProperty.DecodeProperty(encodedProperties, ref offset, dataSize);
                    if (offset - initialOffset != propertySize)
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

        private bool AnyPropertyNeedSync()
        {
            return GetPropertiesToSync().Any();
        }

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
            ushort propID = synchronizedProperty.PropertyID;
            if (m_synchronizedProperties.ContainsKey(propID))
            {
                throw new InvalidDataException($"The ID {propID} is already used by {m_synchronizedProperties[propID]}");
            }
            m_synchronizedProperties.Add(propID, synchronizedProperty);
        }
        #endregion

        // Start is called before the first frame update
        protected virtual void Start()
        {
            LoadProperties();
            NetworkManager.Instance.AddSynchronizedObject(this);
        }
    }
}
