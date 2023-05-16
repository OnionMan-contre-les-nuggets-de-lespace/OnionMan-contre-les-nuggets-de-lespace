using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Computer : MonoBehaviour, IRoomAction
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

    public void LaunchAction()
    {
        Debug.Log("LAUNCHING COMPUTER");
    }
}
