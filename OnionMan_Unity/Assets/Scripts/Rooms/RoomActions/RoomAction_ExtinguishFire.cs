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
