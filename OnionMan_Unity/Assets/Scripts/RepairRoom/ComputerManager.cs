using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System;

public class ComputerManager : MonoBehaviour
{
    [SerializeField] private GameObject m_reparatorWelcomePanel;
    [SerializeField] private GameObject m_winPanel;
    [SerializeField] private Image m_toolImage;
    [SerializeField] private TMP_Text m_winText;
    [SerializeField] private GameObject m_loosePanel;
    [SerializeField] private TMP_Text m_reparatorWelcomingMessage;
    [SerializeField] private GameObject m_beamPanel;
    [SerializeField] private List<GameObject> m_sparklePanelList = new List<GameObject>();
    [SerializeField] private List<Sprite> toolsSpriteList = new List<Sprite>();
    [SerializeField] private List<Color> colorList = new List<Color>();
    [SerializeField] private Canvas mainCanvas;

    [SerializeField] public List<Button> valveButtonList = new List<Button>();
    [SerializeField] public GameObject m_computerPanel;

    private List<GameObject> m_variableSparklePanelList = new List<GameObject>();
    private RoomAction_Computer computerAction;
    private RoomName currentScannedRoom;
    private bool beamPhaseRady; //TODO : SynchronizedProperty

    public Action<ComputerGameResult> OnComputerGameFinished;
    public Vector3Int playerChoices = new Vector3Int(); //x = shape, y = color, z = orientation

    private void Start()
    {
        computerAction = FindObjectOfType<RoomAction_Computer>();
    }

    public void ShowComputer(RoomName roomName)
    {
        mainCanvas.sortingOrder = 15;
        currentScannedRoom = roomName;
        m_computerPanel.SetActive(true);
        m_reparatorWelcomePanel.SetActive(true);
        m_reparatorWelcomingMessage.text = "Bienvenue dans le Reparator v022251212. Vous avez scanné la salle : " + GameManager.userRoomName[currentScannedRoom];
    }

    public void HideComputer()
    {
        mainCanvas.sortingOrder = 0;
        m_reparatorWelcomePanel.SetActive(false);
        m_computerPanel.SetActive(false);
        m_winPanel.SetActive(false);

        computerAction.OnComputerActionEnd?.Invoke();
    }

    private void CheckResult()
    {
        m_winPanel.SetActive(true);
        ComputerGameResult computerGameResult = new ComputerGameResult(colorList, toolsSpriteList, valveButtonList);
        m_winText.text = "Gagne ! Une avarie a ete detectee sur la <u><b> valve " + (computerGameResult.valveIndex + 1).ToString() + "</b></u>. " +
            "Vous pouvez maintenant reparer la salle : " + GameManager.userRoomName[currentScannedRoom] + " grace à l'outil suivant : ";
        m_toolImage.sprite = computerGameResult.correctTool.ToolSprite;
        m_toolImage.color = computerGameResult.correctTool.ToolColor;

        OnComputerGameFinished?.Invoke(computerGameResult);
    }

    public void OC_OnQuitComputerButtonClicked()
    {
        HideComputer();
    }

    public void OC_OnRetryButtonClicked()
    {
        m_loosePanel.SetActive(false);
        m_reparatorWelcomePanel.SetActive(true);
    }

    public void OC_OnProceedButtonClicked()
    {
        m_variableSparklePanelList.Clear();
        m_reparatorWelcomePanel.SetActive(false);

        for (int i = 0; i < m_sparklePanelList.Count; i++)
        {
            m_variableSparklePanelList.Add(m_sparklePanelList[i]);
        }

        int random = UnityEngine.Random.Range(0, m_sparklePanelList.Count);
        m_sparklePanelList[random].SetActive(true);
        m_variableSparklePanelList.RemoveAt(random);
    }

    public void OC_OnShapeButtonClicked(int i)
    {
        playerChoices.x = i;
        m_sparklePanelList[0].SetActive(false);
        if(m_variableSparklePanelList.Count > 0)
        {
            int random = UnityEngine.Random.Range(0, m_variableSparklePanelList.Count);
            m_variableSparklePanelList[random].SetActive(true);
            m_variableSparklePanelList.RemoveAt(random);
        }
        else
        {
            CheckResult();
        }
    }

    public void OC_OnColorButtonClicked(int i)
    {
        playerChoices.y = i;
        m_sparklePanelList[1].SetActive(false);
        if (m_variableSparklePanelList.Count > 0)
        {
            int random = UnityEngine.Random.Range(0, m_variableSparklePanelList.Count);
            m_variableSparklePanelList[random].SetActive(true);
            m_variableSparklePanelList.RemoveAt(random);
        }
        else
        {
            CheckResult();
        }
    }
    public void OC_OnOrientationButtonClicked(int i)
    {
        playerChoices.z = i;
        m_sparklePanelList[2].SetActive(false);
        if (m_variableSparklePanelList.Count > 0)
        {
            int random = UnityEngine.Random.Range(0, m_variableSparklePanelList.Count);
            m_variableSparklePanelList[random].SetActive(true);
            m_variableSparklePanelList.RemoveAt(random);
        }
        else
        {
            CheckResult();
        }
    }
}
