using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class RepairManager : MonoBehaviour
{
    [Header("Reparation")]
    [SerializeField] public GameObject repairPanel;
    [SerializeField] private List<Sprite> toolsSpriteList = new List<Sprite>();
    [SerializeField] private List<Color> colorList = new List<Color>();


    private ComputerManager m_computerManager;
    private RoomManager m_roomManager;
    private RoomName m_scannedRoom;
    private Dictionary<RoomName, MiddleRoom> m_allMiddleRooms = new Dictionary<RoomName, MiddleRoom>();

    private void Start()
    {
        m_computerManager = FindObjectOfType<ComputerManager>();
        m_roomManager = FindObjectOfType<RoomManager>();

        foreach(MiddleRoom room in m_allMiddleRooms.Values)
        {
            room.OnRoomScanned += OnRoomScanned;
        }
    }

    private void OnRoomScanned(RoomName roomName)
    {
        m_scannedRoom = roomName;
        Debug.Log(m_scannedRoom.ToString());
    }

    public void ShowComputer()
    {
        m_computerManager.ShowComputer(m_scannedRoom);
        m_computerManager.OnComputerGameFinished += OnComputerGameFinished;
    }

    public void AddMiddleRoom(MiddleRoom middleRoom)
    {
        m_allMiddleRooms.Add(middleRoom.roomName, middleRoom);
    }

    private void OnComputerGameFinished(ComputerGameResult computerGameResult)
    {
        m_allMiddleRooms[m_scannedRoom].canBeRepaired = true;

        SetupRepairPanel(computerGameResult);
    }

    private void SetupRepairPanel(ComputerGameResult computerGameResult)
    {

    }
}
