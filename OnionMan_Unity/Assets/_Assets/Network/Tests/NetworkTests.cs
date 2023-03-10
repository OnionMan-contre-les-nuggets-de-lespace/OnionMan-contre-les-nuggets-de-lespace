using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;
using System.Linq;
using static UnityEditor.PlayerSettings;

public class NetworkTests : SynchronizedMonoBehaviour
{
    [SerializeField]
    private SynchronizedList<string> SP0;
    [SerializeField]
    private SynchronizedProperty<string> SP1;
    [SerializeField]
    private SynchronizedProperty<Quaternion> SP2;

    [SerializeField]
    private SynchronizedProperty<bool> SP3;
    [SerializeField]
    private string m_encodedObjects;

    public override void LoadProperties()
    {
        AddSynchronizedProperty(SP0);
        AddSynchronizedProperty(SP1);
        AddSynchronizedProperty(SP2);
        AddSynchronizedProperty(SP3);
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
}
