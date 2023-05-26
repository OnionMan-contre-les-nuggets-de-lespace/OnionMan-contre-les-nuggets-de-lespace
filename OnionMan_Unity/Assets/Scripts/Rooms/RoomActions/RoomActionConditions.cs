using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomActionConditions : MonoBehaviour
{
    public static bool hasExtinguisher;
    public static bool hasScannedRoom;
    public static bool collectorIsFull;

    private void Awake()
    {
        hasExtinguisher = false;
        hasScannedRoom = false;
        collectorIsFull = false;
    }
}
