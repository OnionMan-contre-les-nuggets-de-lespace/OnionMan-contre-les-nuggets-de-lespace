using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction : MonoBehaviour
{
    [SerializeField] protected string actionName;
    protected RoomManager roomManager;
    [SerializeField] public List<string> cantBeDoneFeedbackMessageList = new List<string>();

    //public Action OnActionEnd;

    private void Start()
    {
        roomManager = FindObjectOfType<RoomManager>();
    }

    public virtual void LaunchAction(RoomName roomName)
    {

    }

    public virtual bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        indexOfFalseStatement = 0;
        return true;
    }

    public int GetFalseStatementIndex(List<bool> statement, out bool canBeDone)
    {
        int index = 0;
        canBeDone = true;
        for (int i = 0; i < statement.Count; i++)
        {
            if (!statement[i])
            {
                index = i;
                canBeDone = false;
                break;
            }
        }

        return index;
    }

    public virtual string GetActionName()
    {
        return actionName;
    }
}
