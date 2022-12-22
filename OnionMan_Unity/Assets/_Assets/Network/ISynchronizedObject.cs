using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    public interface ISynchronizedObject
    {
        public uint ObjectID {get;}

        public bool NeedSync { get; }

        public Dictionary<ushort, ISynchronizedProperty> Properties { get; }

        public IEnumerable<byte> EncodeObject(bool forSync = true);
        public void DecodeObject(byte[] encodedProperties, ref int offset, int size);
        public void LoadProperties();
    }
}
