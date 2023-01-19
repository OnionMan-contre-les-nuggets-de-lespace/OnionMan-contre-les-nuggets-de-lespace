using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    public interface ISynchronizedObject
    {
        public uint ObjectID {get;}

        public ObjectNeedSyncResult NeedSync();

        public Dictionary<ushort, ISynchronizedProperty> Properties { get; }

        public IEnumerable<byte> EncodeObject(bool forSync = true);
        public void PutEncodedObjectToBuffer(byte[] buffer, ref int offset);

        public void DecodeObject(byte[] encodedProperties, ref int offset, int size);

        public void LoadProperties();
    }

    public struct ObjectNeedSyncResult 
    {
        public bool NeedSync => m_needSync;
        public int EncodedSize => m_encodedSize;

        private bool m_needSync; 
        private int m_encodedSize;

		public ObjectNeedSyncResult(bool needSync, int encodedSize)
		{
            m_needSync = needSync;
            m_encodedSize = encodedSize;
		}
    }
}
