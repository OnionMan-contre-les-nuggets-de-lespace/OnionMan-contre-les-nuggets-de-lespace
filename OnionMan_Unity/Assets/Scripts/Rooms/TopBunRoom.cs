using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TopBunRoom : BunRoom
{
    private RoomAction_Computer computerAction;

    private void Start()
    {
        computerAction = FindObjectOfType<RoomAction_Computer>();
    }

    protected override List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

        roomActions.Add(computerAction);

        return roomActions;
    }
}
