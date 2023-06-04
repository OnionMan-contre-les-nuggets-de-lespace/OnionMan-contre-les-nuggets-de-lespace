using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Repair : RoomAction
{
    [SerializeField] private RepairManager repairManager;
    public Action OnRepairActionEnd;

    public override string GetActionName()
    {
        return actionName;
    }
    public override bool CanBeDone(BaseRoom baseRoom)
    {
        //TODO Empecher l'action d'être faite tant que le mini jeu de l'ordi est pas réussi
        return !RoomActionConditions.hasExtinguisher && !roomManager.middleRooms[baseRoom.roomName].isInCriticalState && roomManager.middleRooms[baseRoom.roomName].canBeRepaired;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        StartCoroutine(RepairCoroutine(currentRoom));
    }

    IEnumerator RepairCoroutine(RoomName roomToScan)
    {
        Debug.Log("LAUNCHING REPAIR");
        repairManager.repairPanel.SetActive(true);
        yield return new WaitUntil(() => repairManager.reparationDone);
        RoomActionConditions.hasScannedRoom = false;
        roomManager.middleRooms[roomToScan].isScanned = false;
        //repairManager.repairPanel.SetActive(false);
        OnRepairActionEnd?.Invoke();
    }
}
