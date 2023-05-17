using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseRoom : MonoBehaviour
{
    [SerializeField] public RoomName roomName;
    [SerializeField] private Canvas mainCanvas;

    protected RoomManager roomManager;
    protected RepairManager repairManager;
    private RoomActionMenu roomActionMenu;

    private void Awake()
    {
        roomManager = FindObjectOfType<RoomManager>();
        roomActionMenu = FindObjectOfType<RoomActionMenu>();
    }

    private void Start()
    {
        roomManager.AddRoom(this);
    }

    public void StartRoomInteraction()
    {
        roomActionMenu.ShowActionMenu(GetActionsToDisplay(), roomName);
        mainCanvas.sortingOrder = 10;
    }

    protected virtual List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

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
    }
}
