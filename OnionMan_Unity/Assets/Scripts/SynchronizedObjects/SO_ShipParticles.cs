using OnionMan.Network;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SO_ShipParticles : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_roomIsScanned;
    [SerializeField] private SynchronizedProperty<Vector3Int> m_rightComputerResultAnswer;

    public SynchronizedProperty<bool> SP_RoomIsScanned
    {
        get => m_roomIsScanned;
    }
    public Vector3Int SP_RightComputerResultAnswer
    {
        get => m_rightComputerResultAnswer.Value;
    }


    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_roomIsScanned);
        AddSynchronizedProperty(m_rightComputerResultAnswer);
    }
}
