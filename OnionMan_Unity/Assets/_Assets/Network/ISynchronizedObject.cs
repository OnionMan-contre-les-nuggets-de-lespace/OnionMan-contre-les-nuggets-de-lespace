using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Network
{
    public interface ISynchronizedObject
    {
        public uint ObjectID {get;}

        public byte[] GetEncodedProperties();
    }
}
