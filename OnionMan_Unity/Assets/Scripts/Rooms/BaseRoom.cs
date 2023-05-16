using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseRoom : MonoBehaviour
{
    [SerializeField] protected RoomName roomName;

    private PlayerMovement playerMovement;
    protected RoomManager roomManager;
    protected RepairManager repairManager;
    private RoomActionMenu roomActionMenu;

    private void Awake()
    {
        roomManager = FindObjectOfType<RoomManager>();
        playerMovement = FindObjectOfType<PlayerMovement>();
        roomActionMenu = FindObjectOfType<RoomActionMenu>();
    }

    private void Start()
    {
        roomManager.AddRoom(this);
    }

    public void StartRoomInteraction()
    {
        roomActionMenu.ShowActionMenu(GetActionsToDisplay());
    }

    protected virtual List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

        return roomActions;
    }

    protected virtual void ResetActionMenu()
    {
        roomActionMenu.HideActionMenu();
    }
}
