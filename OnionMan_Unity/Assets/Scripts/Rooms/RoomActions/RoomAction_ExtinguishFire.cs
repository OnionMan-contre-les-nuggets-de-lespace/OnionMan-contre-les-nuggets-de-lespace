using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_ExtinguishFire : MonoBehaviour, IRoomAction
{
    [SerializeField] private string actionName;

    public string GetActionName()
    {
        return actionName;
    }

    public void LaunchAction()
    {
        Debug.Log("LAUNCHING EXTINGUISH");
    }
}
