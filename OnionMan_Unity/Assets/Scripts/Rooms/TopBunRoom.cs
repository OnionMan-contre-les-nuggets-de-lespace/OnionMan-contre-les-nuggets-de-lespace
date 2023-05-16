using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TopBunRoom : BunRoom
{
    private RoomAction_Computer m_roomActionComputer;

    protected override List<IRoomAction> GetActionsToDisplay()
    {
        return base.GetActionsToDisplay();
    }
}
