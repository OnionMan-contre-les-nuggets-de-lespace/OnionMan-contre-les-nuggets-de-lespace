using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction : MonoBehaviour
{
    [SerializeField] protected string actionName;
    protected RoomManager roomManager;

    //public Action OnActionEnd;

    private void Start()
    {
        roomManager = FindObjectOfType<RoomManager>();
    }

    public virtual void LaunchAction(RoomName roomName)
    {

    }

    public virtual bool CanBeDone(BaseRoom baseRoom)
    {
        return true;
    }

    public virtual string GetActionName()
    {
        return actionName;
    }
}
