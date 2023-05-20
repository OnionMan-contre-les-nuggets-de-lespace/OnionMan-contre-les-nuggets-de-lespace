using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TopBunRoom : BunRoom
{
    private RoomAction_Computer computerAction;
    private RoomAction_TakeFireExtinguisher takeFireExtinguisherAction;

    private void Start()
    {
        computerAction = FindObjectOfType<RoomAction_Computer>();
        takeFireExtinguisherAction = FindObjectOfType<RoomAction_TakeFireExtinguisher>();
    }

    protected override List<RoomAction> GetActionsToDisplay()
    {
        List<RoomAction> roomActions = new List<RoomAction>();

        roomActions.Add(computerAction);
        roomActions.Add(takeFireExtinguisherAction);

        return roomActions;
    }
}
