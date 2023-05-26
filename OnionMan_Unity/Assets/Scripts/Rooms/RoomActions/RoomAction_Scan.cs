using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Scan : RoomAction
{
    [SerializeField] private float scanTime;
    public override bool CanBeDone => !RoomActionConditions.hasExtinguisher;

    public Action OnScanActionEnd;

    public override string GetActionName()
    {
        return actionName;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        StartCoroutine(ScanCoroutine(currentRoom));
    }

    IEnumerator ScanCoroutine(RoomName roomToScan)
    {
        roomManager.middleRooms[roomToScan].scanEffect.SetActive(true);
        Debug.Log("LAUNCHING SCAN");

        yield return new WaitForSeconds(scanTime);

        roomManager.middleRooms[roomToScan].scanEffect.SetActive(false);
        OnScanActionEnd?.Invoke();

        Debug.Log("Scan Action Ended");
    }
}
