using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_TakeFireExtinguisher : RoomAction
{
    [SerializeField] private string nameVariant;

    public Action OnTakeFireExtinguisherActionEnd;


    public override string GetActionName()
    {
        if(RoomActionConditions.hasExtinguisher)
        {
            return nameVariant;
        }
        else
        {
            return actionName;
        }
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        StartCoroutine(TakeExtinguisherCoroutine(currentRoom));
    }

    IEnumerator TakeExtinguisherCoroutine(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING TAKE FIRE EXTINGUISHER");
        RoomActionConditions.hasExtinguisher = !RoomActionConditions.hasExtinguisher;
        yield return new WaitForEndOfFrame();
        OnTakeFireExtinguisherActionEnd?.Invoke();

    }
}
