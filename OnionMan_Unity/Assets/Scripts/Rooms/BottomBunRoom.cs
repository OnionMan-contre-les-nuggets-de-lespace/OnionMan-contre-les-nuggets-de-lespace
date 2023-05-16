using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BottomBunRoom : BunRoom
{
    private RoomAction_Collector collectorAction;

    private void Start()
    {
        collectorAction = FindObjectOfType<RoomAction_Collector>();
    }

    protected override List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

        roomActions.Add(collectorAction);

        return roomActions;
    }
}
