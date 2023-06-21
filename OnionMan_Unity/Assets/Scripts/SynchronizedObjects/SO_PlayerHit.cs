using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_PlayerHit : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_isPlayerHit;
    [SerializeField] private SynchronizedProperty<bool> m_hasReperaidCriticalRoom;

    public SynchronizedProperty<bool> SP_IsPlayerHit
    {
        get => m_isPlayerHit;
    }
    public SynchronizedProperty<bool> HasReperaidCriticalRoom
    {
        get => m_hasReperaidCriticalRoom;
    }

    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_hasReperaidCriticalRoom);
        AddSynchronizedProperty(m_isPlayerHit);
    }
}
