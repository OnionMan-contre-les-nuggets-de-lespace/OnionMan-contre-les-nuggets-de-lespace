using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction : MonoBehaviour
{
    [SerializeField] protected string actionName;
    public virtual bool CanBeDone { get => true ; }
    protected RoomManager roomManager;

    //public Action OnActionEnd;

    private void Awake()
    {
        roomManager = FindObjectOfType<RoomManager>();
    }

    public virtual void LaunchAction(RoomName roomName)
    {

    }

    public virtual string GetActionName()
    {
        return actionName;
    }
}
