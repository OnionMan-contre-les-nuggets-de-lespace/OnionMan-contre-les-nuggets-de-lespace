using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomAction_Repair : RoomAction
{
    public override string GetActionName()
    {
        return actionName;
    }
    public override bool CanBeDone(BaseRoom baseRoom)
    {
        //TODO Empecher l'action d'être faite tant que le mini jeu de l'ordi est pas réussi
        return !RoomActionConditions.hasExtinguisher && !roomManager.middleRooms[baseRoom.roomName].isInCriticalState && roomManager.middleRooms[baseRoom.roomName].isScanned;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING REPAIR");
    }
}
