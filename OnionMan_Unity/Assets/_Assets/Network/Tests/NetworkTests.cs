using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;
using System.Linq;
using static UnityEditor.PlayerSettings;

public class NetworkTests : SynchronizedMonoBehaviour
{
    private enum Enumeuh
	{
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T
	}
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
    [SerializeField]
    private OnionMan.Utils.SerializedDictionary<Enumeuh,float> SP6;

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
        SP0.Init();
        SP1.Init();
        SP2.Init();
        SP3.Init();
        SP4.Init();
        SP5.Init();
        AddSynchronizedProperty(SP0);
        AddSynchronizedProperty(SP1);
        AddSynchronizedProperty(SP2);
        AddSynchronizedProperty(SP3);
        AddSynchronizedProperty(SP4);
        AddSynchronizedProperty(SP5);
    }
}
