using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Collector : RoomAction
{
    [SerializeField] private float collectorActionTime;
    [SerializeField] private UpgradeManager upgradeManager;
    [SerializeField] public SO_CollectorIsFull SO_collectorIsFull;

    public Action OnCollectorActionEnd;

    public override string GetActionName()
    {
        return actionName;
    }
    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;

        statements.Add(!RoomActionConditions.hasExtinguisher);
        statements.Add(SO_collectorIsFull.SP_CollectorIsFull.Value);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);

        return canBeDone;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        base.LaunchAction(currentRoom);
        StartCoroutine(UpgradeCoroutine(currentRoom));
    }

    IEnumerator UpgradeCoroutine(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING COLLECTOR");

        yield return new WaitForSeconds(collectorActionTime);
        SO_collectorIsFull.SP_CollectorIsFull.Value = false;
        upgradeManager.numberOfScrappedPart++;
        OnCollectorActionEnd?.Invoke();
        Debug.Log("Collector Action Ended");
    }
}
