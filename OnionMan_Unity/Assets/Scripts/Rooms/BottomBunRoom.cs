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

    protected override List<RoomAction> GetActionsToDisplay()
    {
        List<RoomAction> roomActions = new List<RoomAction>();

        roomActions.Add(collectorAction);

        return roomActions;
    }
}
