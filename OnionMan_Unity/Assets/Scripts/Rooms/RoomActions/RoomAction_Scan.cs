using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Scan : RoomAction
{
    [SerializeField] private float scanTime;

    public Action OnScanActionEnd;

    public override string GetActionName()
    {
        return actionName;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        base.LaunchAction(currentRoom);
        StartCoroutine(ScanCoroutine(currentRoom));
    }

    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;

        statements.Add(!RoomActionConditions.hasExtinguisher);
        statements.Add(!roomManager.middleRooms[baseRoom.roomName].isScanned);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);


        return canBeDone;
        //return !RoomActionConditions.hasExtinguisher && !roomManager.middleRooms[baseRoom.roomName].isScanned;
    }

    IEnumerator ScanCoroutine(RoomName roomToScan)
    {
        roomManager.middleRooms[roomToScan].scanEffect.SetActive(true);
        Debug.Log("LAUNCHING SCAN");

        yield return new WaitForSeconds(scanTime);

        roomManager.middleRooms[roomToScan].scanEffect.SetActive(false);
        RoomActionConditions.hasScannedRoom = true;

        foreach(MiddleRoom room in roomManager.middleRooms.Values)
        {
            room.isScanned = false;
            room.canBeRepaired = false;
        }

        roomManager.middleRooms[roomToScan].isScanned = true;
        OnScanActionEnd?.Invoke();
        roomManager.middleRooms[roomToScan].OnRoomScanned?.Invoke(roomToScan);

        Debug.Log("Scan Action Ended");
    }
}
