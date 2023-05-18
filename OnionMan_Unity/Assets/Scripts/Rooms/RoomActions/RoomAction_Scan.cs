using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class RoomAction_Scan : MonoBehaviour, IRoomAction
{
    [SerializeField] private List<GameObject> scanEffects = new List<GameObject>();
    [SerializeField] private string actionName;
    [SerializeField] private float scanTime;
    [SerializeField] private bool canBeDone;

    private RoomManager roomManager;
    private Dictionary<RoomName, GameObject> roomScanEffect = new Dictionary<RoomName, GameObject>();

    public Action OnScanActionEnd;
    public bool CanBeDone
    {
        get => true;
    }

    private void Awake()
    {
        roomManager = FindObjectOfType<RoomManager>();
        //roomScanEffect.Add(RoomName.TOMATO, scanEffects[0]);
        //roomScanEffect.Add(RoomName.CHEESE, scanEffects[1]);
        //roomScanEffect.Add(RoomName.STEAK, scanEffects[2]);
        //roomScanEffect.Add(RoomName.SALAD, scanEffects[3]);
    }

    public string GetActionName()
    {
        return actionName;
    }

    public void LaunchAction(RoomName currentRoom)
    {
        StartCoroutine(ScanCoroutine(currentRoom));
    }

    IEnumerator ScanCoroutine(RoomName roomToScan)
    {
        roomManager.middleRooms[roomToScan].scanEffect.SetActive(true);
        Debug.Log("LAUNCHING SCAN");

        yield return new WaitForSeconds(scanTime);

        roomManager.middleRooms[roomToScan].scanEffect.SetActive(false);
        OnScanActionEnd?.Invoke();
        Debug.Log("Scan Action Ended");
    }
}
