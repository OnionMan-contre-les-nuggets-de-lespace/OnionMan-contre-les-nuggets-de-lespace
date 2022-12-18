using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;
using System.Linq;

public class NetworkTests : SynchronizedMonoBehaviour
{
    [SerializeField]
    private SynchronizedProperty<char> SP0;
    [SerializeField]
    private SynchronizedProperty<uint> SP1;
    [SerializeField]
    private SynchronizedProperty<string> SP2;
    [SerializeField]
    private SynchronizedProperty<long> SP3;


    // Update is called once per frame
    void Update()
    {
        
    }

    public void EncodeString()
    {
        NetworkManager.Instance.DecodeObjects(NetworkManager.Instance.EncodeObjectsToSync());
    }

    public override IEnumerable<byte> GetEncodedProperties()
    {
        return SP0.Encode()
            .Concat(SP1.Encode())
            .Concat(SP2.Encode())
            .Concat(SP3.Encode());
    }

    public override void DecodeProperties(byte[] encodedProperties, ref int offset)
    {
        SP0.Decode(encodedProperties, ref offset);
        SP1.Decode(encodedProperties, ref offset);
        SP2.Decode(encodedProperties, ref offset);
        SP3.Decode(encodedProperties, ref offset);
    }
}
