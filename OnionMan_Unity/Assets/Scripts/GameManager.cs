using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Utils;
using System;
using UnityEngine.SceneManagement;
using OnionMan.Network;

public class GameManager : SingletonMonoBehaviour<GameManager>
{
    [SerializeField] private GameObject clickBlocker;
    [SerializeField] private GameObject winGamePanel;
    [SerializeField] private GameObject looseGamePanel;

    public static Action<bool> DisablePlayerNavigation;
    public static Dictionary<RoomName, string> userRoomName = new Dictionary<RoomName, string>()
    {
        { RoomName.TOP_BUN, "Bun supérieur" },
        { RoomName.TOMATO, "Tomate" },
        { RoomName.CHEESE, "Fromage" },
        { RoomName.STEAK, "Steak" },
        { RoomName.SALAD, "Salade" },
        { RoomName.BOTTOM_BUN, "Bun inférieur" }
    };



    private void Awake()
    {
        DisablePlayerNavigation += DisableNavigation;
        NetworkManager.Instance.OnGameStateChanged += OnGameStateChanged;
    }

    private void OnGameStateChanged(int newState)
    {

        switch (newState)
        {
            case 0: // Waiting for Game to Start
                break;

            case 1: // Game Started
                break;

            case 2: // Game Won
                winGamePanel.SetActive(true);
                break;

            case 3: // Game Lost
                looseGamePanel.SetActive(true);
                break;

            default:
                Debug.LogError($"{newState} is not a valid GameState");
                break;
        }
    }

    public void DisableNavigation(bool state)
    {
        clickBlocker.SetActive(state);
    }
}
