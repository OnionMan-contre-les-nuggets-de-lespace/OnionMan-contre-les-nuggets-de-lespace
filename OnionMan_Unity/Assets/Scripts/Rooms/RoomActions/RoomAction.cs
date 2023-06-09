using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction : MonoBehaviour
{
    [SerializeField] protected string actionName;
    [SerializeField] public List<string> cantBeDoneFeedbackMessageList = new List<string>();

    protected RoomManager roomManager;
    protected PlayerAnimatorController playerAnimatorController;

    //public Action OnActionEnd;

    private void Start()
    {
        roomManager = FindObjectOfType<RoomManager>();
        playerAnimatorController = FindObjectOfType<PlayerAnimatorController>();
    }

    public virtual void LaunchAction(RoomName roomName)
    {
        playerAnimatorController.EnterCraftAnimation();
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
