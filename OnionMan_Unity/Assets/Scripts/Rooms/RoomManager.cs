using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomManager : MonoBehaviour
{
    [SerializeField] private List<BaseRoom> m_rooms = new List<BaseRoom>();
    [SerializeField] private bool isPlayerHit; //TODO passer en synchronized property

    private List<MiddleRoom> m_middleRooms = new List<MiddleRoom>();
    private List<BunRoom> m_bunRooms = new List<BunRoom>();

    public Dictionary<RoomName, MiddleRoom> middleRooms = new Dictionary<RoomName, MiddleRoom>();

    private void Update()
    {
        if(isPlayerHit)
        {
            ChooseRoomInCriticalState();
            isPlayerHit = false;
        }
    }

    private void ChooseRoomInCriticalState()
    {
        m_middleRooms[Random.Range(0, m_middleRooms.Count)].isInCriticalState = true;
    }

    public void NotifyRoom(int indexOfRoom)
    {
        m_rooms[indexOfRoom].StartRoomInteraction();
    }

    public void AddMiddleRoom(MiddleRoom middleRoom)
    {
        m_middleRooms.Add(middleRoom);
        middleRooms.Add(middleRoom.roomName, middleRoom);
    }

    public void AddBunRoom(BunRoom bunRoom)
    {
        m_bunRooms.Add(bunRoom);
    }

    public void AddRoom(BaseRoom baseRoom)
    {
        m_rooms.Add(baseRoom);
    }
}
