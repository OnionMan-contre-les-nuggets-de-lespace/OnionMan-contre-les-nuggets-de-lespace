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
    [SerializeField]
    private SynchronizedList<Vector3> SP4;
    [SerializeField]
    private SynchronizedList<string> SP5;

    [SerializeField] private string m_encodedObjects = string.Empty;

    // Update is called once per frame
    void Update()
    {
        
    }

    public void ChangeValues()
    {
        SP4.Value.Add(new Vector3(Random.value, Random.value, Random.value));
        SP5.Value.Add($"Value {Random.value}");
    }

    public void EncodeAndPrint()
    {
        Debug.Log(EncodingUtility.GetBytesAsString(NetworkManager.Instance.EncodeObjects()));
        //NetworkManager.Instance.DecodeObjects(NetworkManager.Instance.EncodeObjects());
    }

    public void TryDecode()
    {
        NetworkManager.Instance.DecodeObjects(EncodingUtility.GetStringAsBytes(m_encodedObjects));
    }

    public override void LoadProperties()
    {
        AddSynchronizedProperty(SP0);
        AddSynchronizedProperty(SP1);
        AddSynchronizedProperty(SP2);
        AddSynchronizedProperty(SP3);
        AddSynchronizedProperty(SP4);
        AddSynchronizedProperty(SP5);
    }
}
