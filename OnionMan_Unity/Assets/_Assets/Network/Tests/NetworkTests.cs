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
        byte[] encoded = GetEncodedProperties();
        int offset = 0;
        var decodedSP0 = SP0.Decode(encoded, ref offset);
        var decodedSP1 = SP1.Decode(encoded, ref offset);
        var decodedSP2 = SP2.Decode(encoded, ref offset);
        var decodedSP3 = SP3.Decode(encoded, ref offset);
        Debug.LogError(EncodingUtility.GetBytesAsString(encoded));
        Debug.LogError(decodedSP0);
        Debug.LogError(decodedSP1);
        Debug.LogError(decodedSP2);
        Debug.LogError(decodedSP3);
    }

    public override byte[] GetEncodedProperties()
    {
        return SP0.Encode()
            .Concat(SP1.Encode())
            .Concat(SP2.Encode())
            .Concat(SP3.Encode())
            .ToArray();
    }
}
