using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Computer : MonoBehaviour, IRoomAction
{
    [SerializeField] private string actionName;
    public string GetActionName()
    {
        return actionName;
    }

    public void LaunchAction()
    {
        throw new System.NotImplementedException();
    }
}
