using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using OnionMan.Network;
using System;
using UnityEngine.SceneManagement;

public class MainMenuController : MonoBehaviour
{
    [SerializeField] private Button m_connectButton;

    [SerializeField] private string m_nextSceneName;

    private void Start()
    {
        m_connectButton.onClick.AddListener(OnConnectButtonClicked);
    }

    private void OnDestroy()
    {
        m_connectButton.onClick.RemoveListener(OnConnectButtonClicked);
    }

    private void OnConnectButtonClicked()
    {
        NetworkManager.Instance.Connect();
        m_connectButton.enabled = false;
        NetworkManager.Instance.OnConnectedToServer += OnConnectedToUnrealServer; 
    }

    private void OnConnectedToUnrealServer()
    {
        NetworkManager.Instance.OnConnectedToServer -= OnConnectedToUnrealServer;
        SceneManager.LoadScene(m_nextSceneName);
    }
}
