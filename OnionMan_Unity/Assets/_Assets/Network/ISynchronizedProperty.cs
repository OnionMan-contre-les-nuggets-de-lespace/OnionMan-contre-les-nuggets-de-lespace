using OnionMan.Network;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public interface ISynchronizedProperty
{
    public bool NeedSync { get; set; }

    public ushort PropertyID { get; }

    public IEnumerable<byte> EncodeProperty(bool forSync = true);

    public void DecodeProperty(byte[] encodedProperty, ref int offset, int propertySize);
}
