using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Utils;
using System;

public class GameManager : SingletonMonoBehaviour<GameManager>
{
    [SerializeField] private GameObject clickBlocker;

    public static Action<bool> DisablePlayerNavigation;

    private void Awake()
    {
        DisablePlayerNavigation += DisableNavigation;
    }

    public void DisableNavigation(bool state)
    {
        clickBlocker.SetActive(state);
    }
}
