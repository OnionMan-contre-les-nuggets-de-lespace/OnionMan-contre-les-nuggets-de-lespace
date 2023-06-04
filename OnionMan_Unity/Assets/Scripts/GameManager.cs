using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Utils;
using System;

public class GameManager : SingletonMonoBehaviour<GameManager>
{
    [SerializeField] private GameObject clickBlocker;

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
    }

    public void DisableNavigation(bool state)
    {
        clickBlocker.SetActive(state);
    }
}
