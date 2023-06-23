using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TMPro;

public class MiddleRoom : BaseRoom
{
    [SerializeField] private int roomHealth;
    [SerializeField] private int reparationHeal;
    [SerializeField] private int healWhenExtinguishFire;
    [SerializeField] private int decayDamage;
    [SerializeField] private Vector2 rangeOfTimerBeforeDecay;
    [SerializeField] private float m_timerBeforeStartDecay;
    [SerializeField] private TMP_Text roomHealthText;
    [SerializeField] protected RepairManager repairManager;
    [SerializeField] private SO_PlayerHit SO_playerHit;

    [Space]

    [Header("Critical State")]
    [SerializeField] private GameObject criticalStateFeedback;
    [SerializeField] private GameObject criticalStateFeedbackVisual;
    [SerializeField] private int numberOfFireToSpawn;
    [SerializeField] private List<RectTransform> fireRectTransform;
    [HideInInspector]
    public List<RectTransform> spawnedFireRectTransform;

    [Space]

    [Header("Scan")]
    [SerializeField] public GameObject scanEffect;
    public bool isScanned; //Set dans la Room Action Scan
    public bool canBeRepaired;

    private float m_timeBeforeDecay;
    private bool m_hasAlreadyEnterCriticalState;

    private RoomAction_Scan scanAction;
    private RoomAction_Repair repairAction;
    private RoomAction_ExtinguishFire extinguishAction;

    public Action<RoomName> OnRoomScanned;
    public bool isInCriticalState;

    protected override void Awake()
    {
        base.Awake();
        repairManager.AddMiddleRoom(this);
        roomManager.AddMiddleRoom(this);
    }


    protected override void Start()
    {
        base.Start();
        scanAction = FindObjectOfType<RoomAction_Scan>();
        repairAction = FindObjectOfType<RoomAction_Repair>();
        extinguishAction = FindObjectOfType<RoomAction_ExtinguishFire>();

        scanAction.OnScanActionEnd += OnFinishedAction;
        //extinguishAction.OnExtinguishActionEnd += OnExtinguishFireActionEnd;
        repairAction.OnRepairActionEnd += OnFinishedAction;
    }

    private void Update()
    {
        roomHealthText.text = roomHealth.ToString() + "%";

        if(isScanned && roomHealth <= 10)
        {
            return;
        }

        if(m_timerBeforeStartDecay > 0)
        {
            m_timerBeforeStartDecay -= Time.deltaTime;
        }

        if(m_timerBeforeStartDecay <= 0)
        {
            if (!isInCriticalState)
            {
                if (m_timeBeforeDecay <= 0)
                {
                    if(roomHealth < decayDamage)
                    {
                        roomHealth -= roomHealth;
                    }
                    else
                    {
                        roomHealth -= decayDamage;
                    }
                    m_timeBeforeDecay = UnityEngine.Random.Range(rangeOfTimerBeforeDecay.x, rangeOfTimerBeforeDecay.y);
                }

                if (m_timeBeforeDecay > 0)
                {
                    m_timeBeforeDecay -= Time.deltaTime;
                }
            }
        }

        if(roomHealth <= 0 || SO_playerHit.SP_IsPlayerHit.Value)
        {
            SO_playerHit.SP_IsPlayerHit.Value = false;
            isInCriticalState = true;
        }
        
        if(isInCriticalState && !m_hasAlreadyEnterCriticalState)
        {
            StepIntoCriticalState();
        }
    }

    protected override List<RoomAction> GetActionsToDisplay()
    {
        List<RoomAction> roomActions = new List<RoomAction>();

        roomActions.Add(scanAction);
        roomActions.Add(repairAction);
        roomActions.Add(extinguishAction);

        return roomActions;
    }
    private void StepIntoCriticalState()
    {
        spawnedFireRectTransform.Clear();
        m_hasAlreadyEnterCriticalState = true;
        criticalStateFeedback.SetActive(true);
        criticalStateFeedbackVisual.SetActive(true);

        Rect fireParentRect = criticalStateFeedback.GetComponent<RectTransform>().rect;

        for (int i = 0; i < numberOfFireToSpawn; i++)
        {
            fireRectTransform[i].gameObject.SetActive(true);

            float offset = 200;

            fireRectTransform[i].anchoredPosition = new Vector2(UnityEngine.Random.Range(fireParentRect.xMin + offset, fireParentRect.xMax - offset), fireRectTransform[i].anchoredPosition.y);
            spawnedFireRectTransform.Add(fireRectTransform[i]);
        }
    }

    public void OnRoomRepaired()
    {
        OnFinishedAction();
        roomHealth += reparationHeal;
        SO_playerHit.SP_HasReperaidCriticalRoom.Value = true;
    }

    public void OnExtinguishFireActionEnd()
    {
        OnFinishedAction();
        roomHealth += healWhenExtinguishFire;
        isInCriticalState = false;
        m_hasAlreadyEnterCriticalState = false;

        for (int i = 0; i < numberOfFireToSpawn; i++)
        {
            fireRectTransform[i].GetComponent<Animator>().Play("End");
            fireRectTransform[i].gameObject.SetActive(false);
        }
        criticalStateFeedback.SetActive(false);
        criticalStateFeedbackVisual.SetActive(false);
    }

    protected override void OnFinishedAction()
    {
        base.OnFinishedAction();        
    }

}
