using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_TakeFireExtinguisher : RoomAction
{
    public override string GetActionName()
    {
        return actionName;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING TAKE FIRE EXTINGUISHER");
        RoomActionConditions.hasExtinguisher = true;
    }
}
