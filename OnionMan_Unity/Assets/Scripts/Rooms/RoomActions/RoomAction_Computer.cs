using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Computer : RoomAction
{
    public override string GetActionName()
    {
        return actionName;
    }

    public override bool CanBeDone(BaseRoom baseRoom)
    {
        return RoomActionConditions.hasScannedRoom;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING COMPUTER");
    }
}
