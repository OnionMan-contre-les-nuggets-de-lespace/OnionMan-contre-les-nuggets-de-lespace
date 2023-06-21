using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BottomBunRoom : BunRoom
{
    [SerializeField] private UpgradeManager upgradeManager;
    private RoomAction_Collector collectorAction;
    private RoomAction_UpgradeWeapon upgradeAction;

    protected override void Start()
    {
        base.Start();
        collectorAction = FindObjectOfType<RoomAction_Collector>();
        upgradeAction = FindObjectOfType<RoomAction_UpgradeWeapon>();

        collectorAction.OnCollectorActionEnd += OnCollectorActionEnd;
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
        if(RoomActionConditions.collectorIsFull)
        {
            //Activer le sprite du collector full
        }
        else
        {
            //Activer le sprite du collector vide
        }
    }

    private void OnCollectorActionEnd()
    {
        RoomActionConditions.collectorIsFull = false; //TODO : Envoyer le call au PC
    }
}
