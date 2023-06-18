using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_IsPlayerHit : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_isPlayerHit;
    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_isPlayerHit);
    }
}
