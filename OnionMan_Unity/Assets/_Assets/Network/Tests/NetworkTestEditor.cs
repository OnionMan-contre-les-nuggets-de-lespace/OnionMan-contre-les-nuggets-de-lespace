using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(NetworkTests))]
public class NetworkTestEditor : Editor
{
    private NetworkTests m_target;
    private void OnEnable()
    {
        m_target = (NetworkTests)target;
    }

    public override void OnInspectorGUI()
    {
        if (GUILayout.Button("Encode"))
        {
            m_target.EncodeAndPrint();
        }
        if (GUILayout.Button("Decode"))
        {
            m_target.TryDecode();
        }
        if (GUILayout.Button("ChangeValue"))
        {
        }
        base.OnInspectorGUI();
    }
}
