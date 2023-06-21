using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;
using UnityEngine.UI;
using TMPro;

public class RepairManager : MonoBehaviour
{
    [Header("Reparation")]
    [SerializeField] public GameObject repairPanel;
    [SerializeField] public GameObject toolsPanel;
    [SerializeField] private TMP_Text instructionText;
    [SerializeField] private GameObject resultPanel;
    [SerializeField] private TMP_Text resultText;
    [SerializeField] private Button[] toolsButton;

    public bool reparationIsSuccess;
    public bool reparationDone;

    private bool rightValveChoosen;
    private int rightAnswerIndex;
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
        reparationDone = false;
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
        instructionText.text = "Sur quelle valve voulez-vous appliquer les réparations ?";
        toolsButton[0].image.sprite = computerGameResult.correctTool.ToolSprite;
        toolsButton[0].image.color = computerGameResult.correctTool.ToolColor;

        toolsButton[1].image.sprite = computerGameResult.badTools[0].ToolSprite;
        toolsButton[1].image.color = computerGameResult.badTools[0].ToolColor;

        toolsButton[2].image.sprite = computerGameResult.badTools[1].ToolSprite;
        toolsButton[2].image.color = computerGameResult.badTools[1].ToolColor;

        foreach(Transform child in toolsPanel.transform)
        {
            child.SetSiblingIndex(Random.Range(0, toolsPanel.transform.childCount));
        }

        for(int i = 0; i < m_computerManager.valveButtonList.Count; i++)
        {
            int x = i;
            m_computerManager.valveButtonList[i].onClick.AddListener(() =>
            {
                m_computerManager.valveButtonList[x].Select();
                toolsPanel.SetActive(true);
                instructionText.text = "Quel outil à utiliser sur la valve ?";

                if(x == computerGameResult.valveIndex)
                {
                    rightValveChoosen = true;
                }
                else
                {
                    rightValveChoosen = false;
                }
            });
        }
    }
    
    public void OC_OnToolClick(int i)
    {
        resultPanel.SetActive(true);
        reparationIsSuccess = i == 0 && rightValveChoosen;
        if(reparationIsSuccess)
        {
            resultText.text = "Réparation réussi ! La salle " + GameManager.userRoomName[m_scannedRoom] + " sera réparée !";
            m_allMiddleRooms[m_scannedRoom].OnRoomRepaired();
            Debug.Log("SUCCES");
        }
        else
        {
            resultText.text = "Réparation ratée !";
            Debug.Log("FAILED");
        }
    }

    public void OC_OnCloseResultPanel()
    {
        toolsPanel.SetActive(false);
        resultPanel.SetActive(false);
        repairPanel.SetActive(false);
        reparationDone = true;
    }
}
