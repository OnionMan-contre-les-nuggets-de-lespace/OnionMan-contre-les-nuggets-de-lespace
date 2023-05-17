using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TMPro;

public class MiddleRoom : BaseRoom
{
    [SerializeField] private int roomHealth;
    [SerializeField] private int decayDamage;
    [SerializeField] private Vector2 rangeOfTimerBeforeDecay;
    [SerializeField] private float m_timerBeforeStartDecay;
    [SerializeField] private TMP_Text roomHealthText;

    private bool m_isInCriticalState;
    private float m_timeBeforeDecay;

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

    private void Update()
    {
        roomHealthText.text = roomHealth.ToString() + "%";

        if(m_timerBeforeStartDecay > 0)
        {
            m_timerBeforeStartDecay -= Time.deltaTime;
        }

        if(m_timerBeforeStartDecay <= 0)
        {
            if (!m_isInCriticalState)
            {
                if (m_timeBeforeDecay <= 0)
                {
                    roomHealth -= decayDamage;
                    m_timeBeforeDecay = UnityEngine.Random.Range(rangeOfTimerBeforeDecay.x, rangeOfTimerBeforeDecay.y);
                }

                if (m_timeBeforeDecay > 0)
                {
                    m_timeBeforeDecay -= Time.deltaTime;
                }
            }
        }
        
    }

    IEnumerator DecayCycleCoroutine()
    {
        yield return new WaitForSeconds(0);
    }
}
