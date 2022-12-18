using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    public interface ISynchronizedObject
    {
        public uint ObjectID {get;}

        public bool NeedSynchronization { get; set; }

        public IEnumerable<byte> GetEncodedProperties();
        public void DecodeProperties(byte[] encodedProperties, ref int offset);
    }
}
