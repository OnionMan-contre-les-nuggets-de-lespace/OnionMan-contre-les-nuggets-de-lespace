using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Repair : RoomAction
{
    [SerializeField] private RepairManager repairManager;
    [SerializeField] private Canvas mainCanvas;

    public Action OnRepairActionEnd;

    public override string GetActionName()
    {
        return actionName;
    }
    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;

        statements.Add(!RoomActionConditions.hasExtinguisher);
        statements.Add(!roomManager.middleRooms[baseRoom.roomName].isInCriticalState);
        statements.Add(roomManager.middleRooms[baseRoom.roomName].canBeRepaired);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);


        return canBeDone;
        //return !RoomActionConditions.hasExtinguisher && !roomManager.middleRooms[baseRoom.roomName].isInCriticalState && roomManager.middleRooms[baseRoom.roomName].canBeRepaired;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        base.LaunchAction(currentRoom);
        StartCoroutine(RepairCoroutine(currentRoom));
    }

    IEnumerator RepairCoroutine(RoomName roomToScan)
    {
        Debug.Log("LAUNCHING REPAIR");
        repairManager.repairPanel.SetActive(true);
        mainCanvas.sortingOrder = 15;
        yield return new WaitUntil(() => repairManager.reparationDone);
        RoomActionConditions.hasScannedRoom = false;
        roomManager.middleRooms[roomToScan].isScanned = false;
        mainCanvas.sortingOrder = 0;

        //repairManager.repairPanel.SetActive(false);
        OnRepairActionEnd?.Invoke();
    }
}
