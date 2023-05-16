using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseRoom : MonoBehaviour
{
    public enum RoomName
    {
        TOP_BUN,
        TOMATO,
        CHEESE,
        STEAK,
        SALAD,
        BOTTOM_BUN,
        NONE
    }

    [SerializeField] protected RoomName roomName;
    protected RoomManager roomManager;
    protected RepairManager repairManager;

    protected virtual List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

        return roomActions;
    }

    protected virtual void ResetActionMenu()
    {

    }
}
