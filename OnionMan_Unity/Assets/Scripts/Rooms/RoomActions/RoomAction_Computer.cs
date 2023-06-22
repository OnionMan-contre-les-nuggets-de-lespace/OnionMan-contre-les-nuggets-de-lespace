using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Computer : RoomAction
{
    [SerializeField] private RepairManager repairManager;

    public Action OnComputerActionEnd;
    public override string GetActionName()
    {
        return actionName;
    }

    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;

        statements.Add(RoomActionConditions.hasScannedRoom);
        statements.Add(!RoomActionConditions.hasExtinguisher);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);


        return canBeDone;
        //return RoomActionConditions.hasScannedRoom;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        base.LaunchAction(currentRoom);
        StartCoroutine(ComputerCoroutine(currentRoom));
    }

    IEnumerator ComputerCoroutine(RoomName currentRoom)
    {
        repairManager.ShowComputer();
        Debug.Log("LAUNCHING COMPUTER");
        yield return new WaitForEndOfFrame();
    }
}
