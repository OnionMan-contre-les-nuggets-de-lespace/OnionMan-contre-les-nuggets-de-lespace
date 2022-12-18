using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    public abstract class SynchronizedMonoBehaviour : MonoBehaviour, ISynchronizedObject
    {
        #region ISynchronizedObject Implementation
        public uint ObjectID { get => m_ObjectID; }
        public bool NeedSynchronization 
        { 
            get => m_needSynchronization; 
            set => m_needSynchronization = value; 
        }

        [SerializeField]
        private uint m_ObjectID;
        [SerializeField]
        private bool m_needSynchronization;

        public abstract IEnumerable<byte> GetEncodedProperties();

        public abstract void DecodeProperties(byte[] encodedProperties, ref int offset);
        #endregion

        // Start is called before the first frame update
        protected virtual void Start()
        {
            NetworkManager.Instance.AddSynchronizedObject(this);
        }
    }
}
