using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Net;
using System.Text;
using UnityEngine;
using UnityEngine.UI;

public class NetworkComponent : MonoBehaviour
{
    //private UdpClient m_udpRecieveClient;
    [SerializeField]
    private UdpClient m_udpSendClient;
    [SerializeField]
    private int m_recievePort = 3001;
    [SerializeField]
    private int m_sendPort = 3002;
    [SerializeField]
    private InputField m_senderPortInput = null;
    [SerializeField]
    private InputField m_recieverPortInput = null;

    [SerializeField]
    private string m_sendIP = "127.0.0.1";
    [SerializeField]
    private InputField m_sendIPInput = null;

    [SerializeField]
    string m_sentMessage = string.Empty;


    bool wasSending = false;

    void Start()
    {
        //m_udpRecieveClient = new UdpClient();
        //m_udpRecieveClient.Client.Bind(new IPEndPoint(IPAddress.Parse(m_sendIP), m_recievePort));
        m_udpSendClient = new UdpClient();
        m_udpSendClient.Client.Bind(new IPEndPoint(IPAddress.Any, int.Parse(m_senderPortInput.text)));

        //StartCoroutine(RecieveCoroutine());

    }

    private void Update()
    {
        if (Input.GetKey(KeyCode.E))
        {
            if (!wasSending)
            {
                SendMessageViaNetwork(m_sentMessage);
            }
        }
        else
        {
            wasSending = false;
        }
    }

    public void SendMessageViaNetwork(string message)
    {
        byte[] data = Encoding.UTF8.GetBytes(message);
        m_udpSendClient.Send(data, data.Length, m_sendIPInput.text, int.Parse(m_recieverPortInput.text));
        Debug.LogWarning("Sent Message");
        wasSending = true;
    }

    private IEnumerator RecieveCoroutine()
    {
        var from = new IPEndPoint(IPAddress.Any, m_recievePort);
        while (Application.isPlaying)
        {
            //var recvBuffer = m_udpRecieveClient.Receive(ref from);
            //Debug.LogError(Encoding.UTF8.GetString(recvBuffer));
            yield return null;
        }
    }
}
