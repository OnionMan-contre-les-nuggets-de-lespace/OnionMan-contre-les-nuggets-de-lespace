using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    public abstract class SynchronizedMonoBehaviour : MonoBehaviour, ISynchronizedObject
    {
        #region ISynchronizedObject Implementation
        public uint ObjectID { get => m_ObjectID; }

        [SerializeField]
        private uint m_ObjectID;

        public abstract byte[] GetEncodedProperties();
        #endregion

        // Start is called before the first frame update
        protected virtual void Start()
        {
            NetworkManager.Instance.AddSynchronizedObject(this);
        }
    }
}
