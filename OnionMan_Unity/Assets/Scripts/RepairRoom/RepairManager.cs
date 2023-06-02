using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RepairManager : MonoBehaviour
{
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

    }

    public void AddMiddleRoom(MiddleRoom middleRoom)
    {
        m_allMiddleRooms.Add(middleRoom.roomName, middleRoom);
    }
}
