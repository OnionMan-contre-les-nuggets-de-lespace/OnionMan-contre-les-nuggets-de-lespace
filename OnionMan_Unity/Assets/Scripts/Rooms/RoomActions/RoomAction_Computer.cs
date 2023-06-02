using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Computer : RoomAction
{
    [SerializeField] private RepairManager repairManager;
    public override string GetActionName()
    {
        return actionName;
    }

    public override bool CanBeDone(BaseRoom baseRoom)
    {
        return RoomActionConditions.hasScannedRoom;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        StartCoroutine(ComputerCoroutine(currentRoom));
    }

    IEnumerator ComputerCoroutine(RoomName currentRoom)
    {
        repairManager.ShowComputer();
        Debug.Log("LAUNCHING COMPUTER");
        yield return new WaitForEndOfFrame();
    }
}
