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
            m_target.EncodeString();
        }
        if (GUILayout.Button("ChangeValue"))
        {
            m_target.ChangeValues();
        }
        base.OnInspectorGUI();
    }
}
