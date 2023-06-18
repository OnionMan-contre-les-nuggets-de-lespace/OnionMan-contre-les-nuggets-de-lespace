using OnionMan.Network;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SO_ShipParticles : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_isRoomScanned;
    public override void LoadProperties()
    {
    }
}
