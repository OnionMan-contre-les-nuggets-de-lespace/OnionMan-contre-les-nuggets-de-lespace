using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomActionConditions : MonoBehaviour
{
    public static bool hasExtinguisher;
    public static bool hasScannedRoom; //TODO : SynchronizedProperty
    public static bool collectorIsFull; //TODO : SynchronizedProperty
    public static bool beamPhaseIsReady; //TODO : SynchronizedProperty

    private void Awake()
    {
        hasExtinguisher = false;
        hasScannedRoom = false;
        collectorIsFull = false;
        beamPhaseIsReady = false;
    }
}
