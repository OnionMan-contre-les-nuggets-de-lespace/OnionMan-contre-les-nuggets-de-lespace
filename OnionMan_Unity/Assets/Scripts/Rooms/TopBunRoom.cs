using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TopBunRoom : BunRoom
{
    private RoomAction_Computer computerAction;
    private RoomAction_TakeFireExtinguisher takeFireExtinguisherAction;

    protected override void Start()
    {
        base.Start();
        computerAction = FindObjectOfType<RoomAction_Computer>();
        takeFireExtinguisherAction = FindObjectOfType<RoomAction_TakeFireExtinguisher>();

        takeFireExtinguisherAction.OnTakeFireExtinguisherActionEnd += OnFinishedAction;
        computerAction.OnComputerActionEnd += OnFinishedAction;
    }

    protected override List<RoomAction> GetActionsToDisplay()
    {
        List<RoomAction> roomActions = new List<RoomAction>();

        roomActions.Add(computerAction);
        roomActions.Add(takeFireExtinguisherAction);

        return roomActions;
    }
}
