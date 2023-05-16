using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class MiddleRoom : BaseRoom
{
    [SerializeField] private int roomHealth;
    [SerializeField] private float timerBeforeDecay;
    [SerializeField] private int decayDamage;
    [SerializeField] private Vector2 rangeOfTimerBeforeDecay;

    private bool m_isInCriticalState;

    private RoomAction_Scan scanAction;
    private RoomAction_Repair repairAction;
    private RoomAction_ExtinguishFire extinguishAction;

    Action<RoomName> OnRoomScanned;



    private void Start()
    {
        roomManager.AddMiddleRoom(this);
        scanAction = FindObjectOfType<RoomAction_Scan>();
        repairAction = FindObjectOfType<RoomAction_Repair>();
        extinguishAction = FindObjectOfType<RoomAction_ExtinguishFire>();
    }

    protected override List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

        roomActions.Add(scanAction);
        roomActions.Add(repairAction);
        roomActions.Add(extinguishAction);

        return roomActions;
    }
}
