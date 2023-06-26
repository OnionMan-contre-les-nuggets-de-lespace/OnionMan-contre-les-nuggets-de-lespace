using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_ExtinguishFire : RoomAction
{
    [SerializeField] private float extinguishTime;
    [SerializeField] private AudioSource alarmAudioSource;
    [SerializeField] private AudioSource extinguisherAudioSource;


    public Action OnExtinguishActionEnd;

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

        statements.Add(roomManager.middleRooms[baseRoom.roomName].isInCriticalState);
        statements.Add(RoomActionConditions.hasExtinguisher);

        indexOfFalseStatement = GetFalseStatementIndex(statements, out canBeDone);


        return canBeDone;
        //return roomManager.middleRooms[baseRoom.roomName].isInCriticalState && RoomActionConditions.hasExtinguisher;
    }

    public override void LaunchAction(RoomName currentRoom)
    {
        base.LaunchAction(currentRoom);
        StartCoroutine(ExtinguishCoroutine(currentRoom));
    }

    IEnumerator ExtinguishCoroutine(RoomName currentRoom)
    {
        Debug.Log("LAUNCHING EXTINGUISH");
        OnExtinguishActionEnd += roomManager.middleRooms[currentRoom].OnExtinguishFireActionEnd;
        extinguisherAudioSource.Play();
        yield return new WaitForSeconds(extinguishTime);
        extinguisherAudioSource.Stop();
        OnExtinguishActionEnd?.Invoke();
        OnExtinguishActionEnd = null;
        bool stopAlarmSound = true;
        foreach (MiddleRoom middleRoom in roomManager.middleRooms.Values)
        {
            if (middleRoom.isInCriticalState)
            {
                stopAlarmSound = false;
            }
        }

        if (stopAlarmSound)
        {
            alarmAudioSource.Stop();
        }
        Debug.Log("Extinguish Action Ended");
    }
}
