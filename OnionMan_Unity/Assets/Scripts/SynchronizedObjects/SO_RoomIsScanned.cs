using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_RoomIsScanned : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_roomIsScanned;
    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_roomIsScanned);
    }
}
