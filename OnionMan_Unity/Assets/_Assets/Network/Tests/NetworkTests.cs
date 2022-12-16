using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;

public class NetworkTests : MonoBehaviour
{
    [SerializeField]
    private SynchronizedProperty<char> st;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void EncodeString()
    {
        byte[] encoded = st.Encode();
        var decoded = EncodingUtility.Decode<char>(encoded, 0);
        Debug.LogError(EncodingUtility.PrintBytes(encoded));
        Debug.LogError(decoded);
    }
}
