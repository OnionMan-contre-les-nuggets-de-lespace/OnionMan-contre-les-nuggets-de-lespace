using UnityEngine;
using UnityEngine.UI;

using OnionMan.Network;
using UnityEngine.SceneManagement;
using TMPro;

public class MainMenuController : MonoBehaviour
{
    [SerializeField] private TMP_InputField m_serverIPInputField;
    [SerializeField] private Button m_connectButton;

    [SerializeField] private string m_waitingToStartMessage;
    [SerializeField] private TMP_Text m_waitingToStartText;

    [SerializeField] private string m_nextSceneName;

    private void Start()
    {
        m_connectButton.onClick.AddListener(OnConnectButtonClicked);
        m_waitingToStartText.gameObject.SetActive(false);
    }

    private void OnDestroy()
    {
        m_connectButton.onClick.RemoveListener(OnConnectButtonClicked);
    }

    private void OnConnectButtonClicked()
    {
        NetworkManager.Instance.Connect(m_serverIPInputField.text);
        m_connectButton.enabled = false;
        NetworkManager.Instance.OnConnectedToServer += OnConnectedToUnrealServer; 
    }

    private void OnConnectedToUnrealServer()
    {
        NetworkManager.Instance.OnConnectedToServer -= OnConnectedToUnrealServer;
        NetworkManager.Instance.OnGameStateChanged += OnGameStateChanged;

        m_serverIPInputField.gameObject.SetActive(false);
        m_connectButton.gameObject.SetActive(false);
        m_waitingToStartText.gameObject.SetActive(true);
    }

    private void OnGameStateChanged(int newState)
    {
        switch (newState)
        {
            case 0: // Waiting for Game to Start
                break;

            case 1: // Game Started
                SceneManager.LoadScene(m_nextSceneName);
                break;

            case 2: // Game Ended
                break;

            default:
                Debug.LogError($"{newState} is not a valid GameState");
                break;
        }
    }
}
