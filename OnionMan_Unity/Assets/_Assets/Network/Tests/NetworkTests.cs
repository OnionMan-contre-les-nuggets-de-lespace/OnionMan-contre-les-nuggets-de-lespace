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
    private SerializableDictionary<int, ulong> dict = new SerializableDictionary<int, ulong>();


    // Update is called once per frame
    void Update()
    {
        
    }

    public void ChangeValues()
    {
        SP0.Value = 'a';
        SP1.Value = 1;
        SP2.Value = "Blaubleubleu";
        SP3.Value = 2;
    }

    public void EncodeString()
    {
        NetworkManager.Instance.DecodeObjects(NetworkManager.Instance.EncodeObjects());
    }

    public override void LoadProperties()
    {
        AddSynchronizedProperty(SP0);
        AddSynchronizedProperty(SP1);
        AddSynchronizedProperty(SP2);
        AddSynchronizedProperty(SP3);
    }
}
