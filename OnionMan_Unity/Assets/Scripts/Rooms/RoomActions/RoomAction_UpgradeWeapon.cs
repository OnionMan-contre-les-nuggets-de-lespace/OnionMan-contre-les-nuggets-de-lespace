using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class RoomAction_UpgradeWeapon : RoomAction
{
    [SerializeField] private float upgradeTime;
    [SerializeField] private UpgradeManager upgradeManager;

    public Action OnUpgradeActionEnd;

    private void Awake()
    {
    }

    public override string GetActionName()
    {
        return actionName;
    }
    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;
        int costOfNextUpgrade;

        statements.Add(!RoomActionConditions.hasExtinguisher);
        statements.Add(upgradeManager.NextUpgradeAvailable(out costOfNextUpgrade));

        cantBeDoneFeedbackMessageList[1] = "Vous devez disposer de " + costOfNextUpgrade + " pièces détachées pour améliorer l'arme";

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
        Debug.Log("LAUNCHING UPGRADE");

        yield return new WaitForSeconds(upgradeTime);
        upgradeManager.UpgradeWeapon();
        upgradeManager.UpdateScrappedPartCountText();
        OnUpgradeActionEnd?.Invoke();
        Debug.Log("Upgrade Action Ended");
    }
}
