using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Repair : MonoBehaviour, IRoomAction
{
    [SerializeField] private string actionName;
    public bool CanBeDone
    {
        get => true;
    }


    public string GetActionName()
    {
        return actionName;
    }

    public void LaunchAction(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING REPAIR");
    }
}
