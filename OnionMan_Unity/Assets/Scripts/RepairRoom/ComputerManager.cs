using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System;
using DG.Tweening;

public class ComputerManager : MonoBehaviour
{
    [SerializeField] private GameObject m_reparatorWelcomePanel;
    [SerializeField] private GameObject m_winPanel;
    [SerializeField] private Image m_toolImage;
    [SerializeField] private TMP_Text m_winText;
    [SerializeField] private GameObject m_loosePanel;
    [SerializeField] private TMP_Text m_reparatorWelcomingMessage;
    [SerializeField] private GameObject m_desktopIcons;
    [SerializeField] private List<GameObject> m_sparklePanelList = new List<GameObject>();
    [SerializeField] private List<Sprite> toolsSpriteList = new List<Sprite>();
    [SerializeField] private List<Color> colorList = new List<Color>();
    [SerializeField] private Canvas mainCanvas;
    [SerializeField] private AudioSource computerAudioSource;
    [SerializeField] private AudioClip failedComputerGameClip;
    [Space]
    [Header("Beam Panel")]
    [SerializeField] private GameObject m_beamPanel;
    [SerializeField] private GameObject m_beamDesktopIcon;
    [SerializeField] private GameObject m_installationPanel;
    [SerializeField] private Slider m_installProgressionSlider;
    [SerializeField] private GameObject m_beamSetupPanel;
    [SerializeField] private GameObject m_beamisReadyPanel;


    [SerializeField] public List<Button> valveButtonList = new List<Button>();
    [SerializeField] public GameObject m_computerPanel;
    [SerializeField] private SO_ShipParticles SO_ShipParticles;

    private List<GameObject> m_variableSparklePanelList = new List<GameObject>();
    private RoomAction_Computer m_computerAction;
    private RoomAction_InstallBeamSetup m_installAction;
    private RoomName currentScannedRoom;

    public Action<ComputerGameResult> OnComputerGameFinished;
    public Vector3Int playerChoices = new Vector3Int(); //x = shape, y = color, z = orientation


    private bool beamIsReady; //TODO : SynchronizedProperty


    private void Start()
    {
        beamIsReady = false;
        m_computerAction = FindObjectOfType<RoomAction_Computer>();
        m_installAction = FindObjectOfType<RoomAction_InstallBeamSetup>();
        m_installAction.OnInstallStarted += StartBeamInstallation;
    }

    public void ShowComputer(RoomName roomName)
    {
        mainCanvas.sortingOrder = 15;
        currentScannedRoom = roomName;
        m_computerPanel.SetActive(true);
    }

    public void HideComputer()
    {
        mainCanvas.sortingOrder = 0;
        m_reparatorWelcomePanel.SetActive(false);
        m_computerPanel.SetActive(false);
        m_winPanel.SetActive(false);
        m_loosePanel.SetActive(false);
        m_desktopIcons.SetActive(true);

        m_computerAction.OnComputerActionEnd?.Invoke();
    }

    private void CheckResult()
    {
        if(playerChoices == SO_ShipParticles.SP_RightComputerResultAnswer)
        {
            m_winPanel.SetActive(true);
            ComputerGameResult computerGameResult = new ComputerGameResult(colorList, toolsSpriteList, valveButtonList);
            m_winText.text = "Gagne ! Une avarie a ete detectee sur la <u><b> valve " + (computerGameResult.valveIndex + 1).ToString() + "</b></u>. " +
                "Vous pouvez maintenant reparer la salle : " + GameManager.userRoomName[currentScannedRoom] + " grace à l'outil suivant : ";
            m_toolImage.sprite = computerGameResult.correctTool.ToolSprite;
            m_toolImage.color = computerGameResult.correctTool.ToolColor;
            OnComputerGameFinished?.Invoke(computerGameResult);
            SO_ShipParticles.SP_RoomIsScanned.Value = false;
        }
        else
        {
            m_loosePanel.SetActive(true);
            computerAudioSource.PlayOneShot(failedComputerGameClip);
        }

    }

    private void StartBeamInstallation(float installTime)
    {
        mainCanvas.sortingOrder = 15;
        m_reparatorWelcomePanel.SetActive(false);
        m_desktopIcons.SetActive(false);
        m_computerPanel.SetActive(true);
        m_beamPanel.SetActive(true);
        m_installationPanel.SetActive(true);

        Sequence seq = DOTween.Sequence();
        seq.Insert(0, m_installProgressionSlider.DOValue(1, installTime));
        seq.AppendCallback(() =>
        {
            m_desktopIcons.SetActive(true);
            m_installationPanel.SetActive(false);
            m_beamPanel.SetActive(false);
            m_beamDesktopIcon.SetActive(true);
            m_installAction.SO_beamPhase.SP_BeamIsReady.Value = true;
        });

        seq.Play();


        //StartCoroutine(InstallationCoroutine(installTime));
    }

    IEnumerator InstallationCoroutine(float installTime)
    {
        m_reparatorWelcomePanel.SetActive(false);
        m_computerPanel.SetActive(true);
        m_beamPanel.SetActive(true);
        m_installationPanel.SetActive(true);

        yield return new WaitForSeconds(installTime);

        m_installationPanel.SetActive(false);
        m_beamPanel.SetActive(false);
        m_beamDesktopIcon.SetActive(true);
    }

    public void OC_OnReparatorIconClicked()
    {
        m_desktopIcons.SetActive(false);
        m_reparatorWelcomePanel.SetActive(true);
        m_reparatorWelcomingMessage.text = "Bienvenue dans le Reparator v022251212. Vous avez scanné la salle : " + GameManager.userRoomName[currentScannedRoom];
    }

    public void OC_OnBeamSetupIconClicked()
    {
        m_desktopIcons.SetActive(false);
        m_beamPanel.SetActive(true);
        m_beamSetupPanel.SetActive(true);
    }

    public void OC_OnSetupButtonClicked()
    {
        beamIsReady = true;
        m_beamSetupPanel.SetActive(false);
        m_beamisReadyPanel.SetActive(true);
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
