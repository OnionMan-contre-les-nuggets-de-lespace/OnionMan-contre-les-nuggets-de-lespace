using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseRoom : MonoBehaviour
{
    [SerializeField] public RoomName roomName;
    [SerializeField] private Canvas mainCanvas;

    protected RoomManager roomManager;
    protected RepairManager repairManager;
    protected PlayerMovement playerMovement;
    private RoomActionMenu roomActionMenu;

    private void Awake()
    {
        roomManager = FindObjectOfType<RoomManager>();
        roomActionMenu = FindObjectOfType<RoomActionMenu>();
        playerMovement = FindObjectOfType<PlayerMovement>();
    }

    private void Start()
    {
        roomManager.AddRoom(this);
    }

    public void StartRoomInteraction()
    {
        roomActionMenu.ShowActionMenu(GetActionsToDisplay(), this);
        mainCanvas.sortingOrder = 10;
    }

    protected virtual List<RoomAction> GetActionsToDisplay()
    {
        List<RoomAction> roomActions = new List<RoomAction>();

        return roomActions;
    }

    protected virtual void ResetActionMenu()
    {
        roomActionMenu.HideAndResetActionMenu();
    }

    protected virtual void OnFinishedAction()
    {
        roomActionMenu.HideAndResetActionMenu();
        mainCanvas.sortingOrder = 0;
        GameManager.DisablePlayerNavigation(false);
    }
}
