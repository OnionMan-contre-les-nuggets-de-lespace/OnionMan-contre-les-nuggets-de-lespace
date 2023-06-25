using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BottomBunRoom : BunRoom
{
    [SerializeField] private UpgradeManager upgradeManager;
    private RoomAction_Collector collectorAction;
    private RoomAction_UpgradeWeapon upgradeAction;
    [SerializeField] private GameObject emptyCollector;

    protected override void Start()
    {
        base.Start();
        collectorAction = FindObjectOfType<RoomAction_Collector>();
        upgradeAction = FindObjectOfType<RoomAction_UpgradeWeapon>();

        collectorAction.OnCollectorActionEnd += OnFinishedAction;
        upgradeAction.OnUpgradeActionEnd += OnFinishedAction;
    }

    protected override List<RoomAction> GetActionsToDisplay()
    {
        List<RoomAction> roomActions = new List<RoomAction>();

        roomActions.Add(collectorAction);
        roomActions.Add(upgradeAction);

        return roomActions;
    }

    private void Update()
    {
        if(collectorAction.SO_collectorIsFull.SP_CollectorIsFull.Value)
        {
            emptyCollector.SetActive(false);
        }
        else
        {
            emptyCollector.SetActive(true);
        }
    }

    private void OnCollectorActionEnd()
    {
        RoomActionConditions.collectorIsFull = false; //TODO : Envoyer le call au PC
    }
}
