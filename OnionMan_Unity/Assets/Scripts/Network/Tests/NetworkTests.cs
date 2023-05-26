using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;
using System.Linq;

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
        //Debug.Log(EncodingUtility.GetBytesAsString(NetworkManager.Instance.TryEncodeObjects()));
        //NetworkManager.Instance.DecodeObjects(NetworkManager.Instance.EncodeObjects());
    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.R)) { RandomizeValues(); }
    }

    public void RandomizeValues()
    {
        int SP0NewCount = Random.Range(2, 10);
        SP0.Value.Clear();
        for (int i = 0; i < SP0NewCount; i++)
        {
            SP0.Value.Add(GetRandomString());
        }

        SP2.Value = new Quaternion(Random.value, Random.value, Random.value, Random.value);

        SP3.Value = Random.value > 0.5f;

        Debug.LogError($"RandomizedValues");
    }

    private string GetRandomString()
    {
        int stringLen = Random.Range(5, 20);
        byte[] encodedString = new byte[stringLen * 2];
        for (int i = 0; i < stringLen * 2; i++) 
        {
            encodedString[i] = (byte)Random.Range(0, 256);
        }
        int offset = 0;
        string randomString = EncodingUtility.Decode<string>(encodedString, ref offset, stringLen);
        Debug.LogError(randomString);
        return randomString;
    }

    public void TryDecode()
    {
        NetworkManager.Instance.DecodeObjects(EncodingUtility.GetStringAsBytes(m_encodedObjects));
    }
}
