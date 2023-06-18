using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;

public class SO_GameState : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<int> m_gameState;

    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_gameState);
    }
}
