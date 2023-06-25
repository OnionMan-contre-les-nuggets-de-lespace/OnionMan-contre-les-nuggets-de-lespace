using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RoomManager : MonoBehaviour
{
    [SerializeField] private List<BaseRoom> m_rooms = new List<BaseRoom>();
    [SerializeField] private bool isPlayerHit; //TODO passer en synchronized property
    [SerializeField] private SO_PlayerHit SO_playerHit;

    private List<MiddleRoom> m_middleRooms = new List<MiddleRoom>();
    private List<BunRoom> m_bunRooms = new List<BunRoom>();

    public Dictionary<RoomName, MiddleRoom> middleRooms = new Dictionary<RoomName, MiddleRoom>();
    public Dictionary<RoomName, BaseRoom> allRooms = new Dictionary<RoomName, BaseRoom>();

    private void Start()
    {
        SO_playerHit.SP_IsPlayerHit.OnValueChanged += CheckIfHit;
    }

    private void CheckIfHit(bool isPlayerHit)
    {
        if (isPlayerHit)
        {
            ChooseRoomInCriticalState();
            SO_playerHit.SP_IsPlayerHit.Value = false;
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
        allRooms.Add(baseRoom.roomName, baseRoom);
        m_rooms.Add(baseRoom);
    }
}
