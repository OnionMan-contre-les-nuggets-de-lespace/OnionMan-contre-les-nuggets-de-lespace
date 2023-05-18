using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_ExtinguishFire : MonoBehaviour, IRoomAction
{
    [SerializeField] private string actionName;
    [SerializeField] private float extinguishTime;

    public Action OnExtinguishActionEnd;

    public bool CanBeDone
    {
        get => true;
    }

    private void Awake()
    {
    }

    public string GetActionName()
    {
        return actionName;
    }

    public void LaunchAction(RoomName currentRoom)
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
