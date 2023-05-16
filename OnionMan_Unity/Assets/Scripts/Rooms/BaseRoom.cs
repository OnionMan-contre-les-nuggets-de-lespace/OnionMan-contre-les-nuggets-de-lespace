using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BaseRoom : MonoBehaviour
{
    [SerializeField] protected RoomName roomName;

    private PlayerMovement playerMovement;
    protected RoomManager roomManager;
    protected RepairManager repairManager;

    private void Awake()
    {
        roomManager = FindObjectOfType<RoomManager>();
        playerMovement = FindObjectOfType<PlayerMovement>();
    }

    private void Start()
    {
        roomManager.AddRoom(this);
    }

    public void StartRoomInteraction()
    {

    }

    protected virtual List<IRoomAction> GetActionsToDisplay()
    {
        List<IRoomAction> roomActions = new List<IRoomAction>();

        return roomActions;
    }

    protected virtual void ResetActionMenu()
    {

    }
}
