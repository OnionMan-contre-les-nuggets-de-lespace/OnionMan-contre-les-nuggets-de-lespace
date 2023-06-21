using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_IndexOfCurrentWeapon : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<int> m_indexOfCurrentWeapon;
    public SynchronizedProperty<int> SP_IndexOfCurrentWeapon
    {
        get => m_indexOfCurrentWeapon;
    }

    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_indexOfCurrentWeapon);
    }
}
