using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

using OnionMan.Network;

public class MainManuController : MonoBehaviour
{
    [SerializeField] private Button m_connectButton;

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
    }
}
