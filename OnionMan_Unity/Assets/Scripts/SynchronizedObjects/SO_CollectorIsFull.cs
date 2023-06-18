using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_CollectorIsFull : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_collectorIsFull;
    public SynchronizedProperty<bool> SP_CollectorIsFull
    {
        get => m_collectorIsFull;
    }

    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_collectorIsFull);
    }
}
