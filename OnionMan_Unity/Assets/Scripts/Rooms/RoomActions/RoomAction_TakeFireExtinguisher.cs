using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_TakeFireExtinguisher : RoomAction
{
    [SerializeField] private string nameVariant;
    [SerializeField] private GameObject playerExtinguisherSprite;
    [SerializeField] private GameObject sceneryExtinguisherSprite;

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
        base.LaunchAction(currentRoom);
        StartCoroutine(TakeExtinguisherCoroutine(currentRoom));
    }

    IEnumerator TakeExtinguisherCoroutine(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING TAKE FIRE EXTINGUISHER");
        RoomActionConditions.hasExtinguisher = !RoomActionConditions.hasExtinguisher;
        playerExtinguisherSprite.SetActive(RoomActionConditions.hasExtinguisher);
        sceneryExtinguisherSprite.SetActive(!RoomActionConditions.hasExtinguisher);
        yield return new WaitForEndOfFrame();
        OnTakeFireExtinguisherActionEnd?.Invoke();

    }
}
