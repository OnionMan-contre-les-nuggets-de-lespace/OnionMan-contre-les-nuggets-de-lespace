using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_InstallBeamSetup : RoomAction
{
    [SerializeField] private float installTime;

    public Action<float> OnInstallStarted;
    public Action OnInstallActionEnd;

    public override string GetActionName()
    {
        return actionName;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        base.LaunchAction(currentRoom);
        StartCoroutine(InstallationCoroutine(currentRoom));
    }

    public override bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        List<bool> statements = new List<bool>();

        bool canBeDone;

        statements.Add(!RoomActionConditions.beamPhaseIsReady);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);


        return canBeDone;
    }

    IEnumerator InstallationCoroutine(RoomName roomToScan)
    {
        Debug.Log("LAUNCHING INSTALL");

        OnInstallStarted?.Invoke(installTime);
        yield return new WaitForEndOfFrame();
        OnInstallActionEnd?.Invoke();

        Debug.Log("Install Action Ended");
    }
}
