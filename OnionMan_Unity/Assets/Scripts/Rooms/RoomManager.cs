using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomManager : MonoBehaviour
{
    [SerializeField] private List<BaseRoom> m_rooms = new List<BaseRoom>();
    private List<MiddleRoom> m_middleRooms = new List<MiddleRoom>();
    private List<BunRoom> m_bunRooms = new List<BunRoom>();

    public void NotifyRoom(int indexOfRoom)
    {
        m_rooms[indexOfRoom].StartRoomInteraction();
    }

    public void AddMiddleRoom(MiddleRoom middleRoom)
    {
        m_middleRooms.Add(middleRoom);
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
