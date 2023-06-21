using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using OnionMan.Network;
using System;

public class SO_GameState : SynchronizedMonoBehaviour
{
    public int CurrentState => m_gameState.Value;

    public Action<int> OnGameStateChange;

    [SerializeField] private SynchronizedProperty<int> m_gameState;

    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_gameState);
    }

    protected override void Start()
    {
        base.Start();
        m_gameState.OnValueChanged += OnGameStateChanged;
    }

    private void OnDestroy()
    {
        m_gameState.OnValueChanged -= OnGameStateChanged;
    }

    private void OnGameStateChanged(int newState)
    {
        OnGameStateChange?.Invoke(newState);
    }
}
