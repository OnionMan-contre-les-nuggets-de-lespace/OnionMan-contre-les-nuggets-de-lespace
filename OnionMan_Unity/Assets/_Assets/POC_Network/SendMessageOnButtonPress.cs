using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SendMessageOnButtonPress : MonoBehaviour
{
    [SerializeField]
    private Button m_sendButton = null;
    [SerializeField]
    private InputField m_inputField = null;
    [SerializeField]
    private NetworkComponent m_networkComponent = null;
    // Start is called before the first frame update
    void Start()
    {
        m_sendButton.onClick.AddListener(SendString);
    }

    private void OnDestroy()
    {
        m_sendButton.onClick.RemoveListener(SendString);
    }

    private void SendString()
    {
        string message = m_inputField.text;
        Debug.LogError($"Sending message : {message}");
        m_networkComponent.SendMessageViaNetwork(message);
    }
}
