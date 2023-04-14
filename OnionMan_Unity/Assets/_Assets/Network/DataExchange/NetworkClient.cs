using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;
using System.Threading;
using UnityEditor.Experimental.GraphView;

public class NetworkClient : MonoBehaviour
{
    [SerializeField] private string m_ip;
    [SerializeField] private int m_port;

    [SerializeField] private int m_classInstanceValue = 0;

    Thread m_networkThread;
    TcpClient m_tcpClient;
    private bool m_networkThreadIsRuning;

    // Start is called before the first frame update
    void Start()
    {
        m_networkThread = new Thread(new ThreadStart(ThreadTest));
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.S)) 
        {
            if (m_networkThread.ThreadState == ThreadState.Stopped)
            {
            }
            Debug.LogError($"Thread State {m_networkThread.ThreadState}");
            m_networkThread.Start();
        }
        if (Input.GetKeyDown(KeyCode.C))
        {
            m_classInstanceValue++;
            Debug.LogError($"Changed Value to {m_classInstanceValue}");
        }
        if (Input.GetKeyDown(KeyCode.R))
        {
            m_networkThread = new Thread(new ThreadStart(ThreadTest));
            Debug.LogError("Rebuild thread");
        }
    }

    private void Initialize()
    {
        m_tcpClient = new TcpClient(m_ip, m_port);
    }

    private void ThreadTest()
    {
        Debug.LogError("StartThread");
        Thread.Sleep(1000);
        Debug.LogError($"Class Instance Value = {m_classInstanceValue}");
        Thread.Sleep(1000);
        Debug.LogError("StartEnd");
    }

    private void Connect()
    {
        while (m_networkThreadIsRuning)
        {
            try
            {
                // Create a TcpClient.
                // Note, for this client to work you need to have a TcpServer
                // connected to the same address as specified by the server, port
                // combination.
                Int32 port = 13000;

                // Prefer a using declaration to ensure the instance is Disposed later.
                using TcpClient client = new TcpClient();

                string s = "message";
                // Translate the passed message into ASCII and store it as a Byte array.
                byte[] data = System.Text.Encoding.ASCII.GetBytes(s);

                // Get a client stream for reading and writing.
                NetworkStream stream = client.GetStream();

                // Send the message to the connected TcpServer.
                stream.Write(data, 0, data.Length);

                Console.WriteLine("Sent: {0}", s);

                // Receive the server response.

                // Buffer to store the response bytes.
                data = new Byte[256];

                // String to store the response ASCII representation.
                String responseData = String.Empty;

                // Read the first batch of the TcpServer response bytes.
                Int32 bytes = stream.Read(data, 0, data.Length);
                responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                Console.WriteLine("Received: {0}", responseData);

                // Explicit close is not necessary since TcpClient.Dispose() will be
                // called automatically.
                // stream.Close();
                // client.Close();
            }
            catch (ArgumentNullException e)
            {
                Console.WriteLine("ArgumentNullException: {0}", e);
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
            }

            Console.WriteLine("\n Press Enter to continue...");
            Console.Read();
        }
    }
}
