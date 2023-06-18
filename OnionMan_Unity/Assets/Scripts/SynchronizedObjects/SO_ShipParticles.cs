using OnionMan.Network;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SO_ShipParticles : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_roomIsScanned;
    [SerializeField] private SynchronizedProperty<Vector3Int> m_rightComputerResultAnswer;
    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_roomIsScanned);
        AddSynchronizedProperty(m_rightComputerResultAnswer);
    }
}
