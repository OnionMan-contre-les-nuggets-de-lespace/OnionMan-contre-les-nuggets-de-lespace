using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Scan : MonoBehaviour, IRoomAction
{
    [SerializeField] private string actionName;
    [SerializeField] private bool canBeDone;
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
        Debug.Log("LAUNCHING SCAN");
    }
}
