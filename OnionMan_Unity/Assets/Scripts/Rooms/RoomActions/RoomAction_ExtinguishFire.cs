using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_ExtinguishFire : RoomAction
{
    [SerializeField] private float extinguishTime;

    public Action OnExtinguishActionEnd;

    private void Awake()
    {
    }

    public override string GetActionName()
    {
        return actionName;
    }
    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;

        statements.Add(roomManager.middleRooms[baseRoom.roomName].isInCriticalState);
        statements.Add(RoomActionConditions.hasExtinguisher);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);


        return canBeDone;
        //return roomManager.middleRooms[baseRoom.roomName].isInCriticalState && RoomActionConditions.hasExtinguisher;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        StartCoroutine(ExtinguishCoroutine(currentRoom));
    }

    IEnumerator ExtinguishCoroutine(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING EXTINGUISH");

        yield return new WaitForSeconds(extinguishTime);

        OnExtinguishActionEnd?.Invoke();
        Debug.Log("Extinguish Action Ended");
    }
}
