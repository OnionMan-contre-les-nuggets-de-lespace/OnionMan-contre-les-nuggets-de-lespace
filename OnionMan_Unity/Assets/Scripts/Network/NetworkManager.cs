using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;

using UnityEngine;

using OnionMan.Utils;

namespace OnionMan.Network
{
    public class NetworkManager : SingletonMonoBehaviour<NetworkManager>
    {
        private enum ConnectionState
        {
            Disconnected,
            WatingForServerResponse,
            Connected,
        }

        private class BatchInfos
        {
            public List<ISynchronizedObject> ObjectsToSync;
            public int BatchSize;

            public BatchInfos(List<ISynchronizedObject> objects, int batchSize)
            {
                ObjectsToSync = objects;
                BatchSize = batchSize;
            }
        }

        public Action OnConnectedToServer;
        public Action<int> OnGameStateChanged;

        public int GameState => m_gameState.CurrentState;

        [SerializeField] private string m_acknoledgeMessage = "ServerAck";

        [SerializeField] private int m_senderPort = 0;
        [SerializeField] private int m_recieverPort = 0;

        [Space]
        [SerializeField] private SO_GameState m_gameState;

        private const int MAX_BATCH_SIZE = 8192;

        private Dictionary<uint, ISynchronizedObject> m_synchronizedObjects = new Dictionary<uint, ISynchronizedObject>();

        private IPEndPoint m_recieverEndPoint;
        private UdpClient m_udpClientReciever;
        private UdpClient m_udpClient;

        private ConnectionState m_connectionState = ConnectionState.Disconnected;


        public NetworkManager()
        {

        }

        protected override void Start()
        {
            base.Start();
            m_gameState.OnGameStateChange += OnGameStateChange;
            m_connectionState = ConnectionState.Disconnected;
        }

        private void Update()
        {
            if (m_connectionState == ConnectionState.Connected)
            {
            }
        }

        protected virtual void LateUpdate()
        {
            SendDataIfNeeded();
            RecieveDataIfAvailable();
        }

        private void OnApplicationQuit()
        {
            Dispose();
        }

        public override void OnDestroy()
        {
            base.OnDestroy();
            Dispose();
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        private void Dispose()
        {
            m_udpClient?.Close();
            m_udpClient?.Dispose();
            m_gameState.OnGameStateChange -= OnGameStateChange;
            //m_udpClientReciever?.Close();
            //m_udpClientReciever?.Dispose();
        }

        public void Connect(string serverIP)
        {
            if (m_connectionState == ConnectionState.Disconnected)
            {
                m_udpClientReciever = new UdpClient(m_recieverPort);

                IPEndPoint senderEndPoint = new IPEndPoint(IPAddress.Parse(serverIP), m_senderPort);
                m_udpClient = new UdpClient();
                m_udpClient.Connect(senderEndPoint);

                // Sends the Ip to the server
                byte[] encodedIP = EncodingUtility.Encode(GetCurrentIP().ToString()).ToArray();

                m_udpClient.Send(encodedIP, encodedIP.Length);

                m_connectionState = ConnectionState.WatingForServerResponse;
            }
        }

        private void SendDataIfNeeded()
        {
            if(m_connectionState == ConnectionState.Connected)
            {
                if (TryEncodeObjects(out List<byte[]> encodedObjectsBatches))
                {
                    foreach (byte[] batch in encodedObjectsBatches)
                    {
                        m_udpClient.Send(batch, batch.Length);
                    }
                }
            }
        }

        private void RecieveDataIfAvailable()
        {
            if (m_connectionState != ConnectionState.Disconnected)
            {
                if (m_udpClientReciever.Available != 0)
                {
                    byte[] recievedBytes = m_udpClientReciever.Receive(ref m_recieverEndPoint);
                    Debug.LogError($"[Frame {Time.frameCount}] {m_udpClientReciever.Available} bytes available");
                    Debug.LogError($"Recieved {recievedBytes.Length} bytes from IP {m_recieverEndPoint.Address} and port {m_recieverEndPoint.Port}");
                    Debug.LogError($"Bytes Recieved : {EncodingUtility.GetBytesAsString(recievedBytes)}");

                    switch (m_connectionState)
                    {
                        case ConnectionState.Disconnected:
                            break;

                        case ConnectionState.WatingForServerResponse:
                            int offset = 0;
                            string decodedResponse = EncodingUtility.Decode<string>(recievedBytes, ref offset, recievedBytes.Length);
                            if (decodedResponse == m_acknoledgeMessage)
                            {
                                m_connectionState = ConnectionState.Connected;
                                OnConnectedToServer?.Invoke();
                            }
                            break;

                        case ConnectionState.Connected:
                            DecodeObjects(recievedBytes);
                            break;
                    }
                }
            }
        }

        
        public void AddSynchronizedObject(ISynchronizedObject obj)
        {
            uint objID = obj.ObjectID;
            if (m_synchronizedObjects.ContainsKey(objID))
            {
                throw new InvalidDataException($"The ID {objID} is already used by {m_synchronizedObjects[objID]}");
            }
            m_synchronizedObjects.Add(objID, obj);
        }

        public void RemoveSynchronizedObject(ISynchronizedObject obj)
        {
            uint objID = obj.ObjectID;
            if (!m_synchronizedObjects.ContainsKey(objID))
            {
                throw new InvalidDataException($"No object with ID {objID}");
            }
            m_synchronizedObjects.Remove(objID);
        }

        public IEnumerable<(ISynchronizedObject, int)> GetObjectsToSync()
        {
            foreach (ISynchronizedObject synchronizedObject in m_synchronizedObjects.Values)
            {
                ObjectNeedSyncResult needSyncResult = synchronizedObject.NeedSync();
                if (needSyncResult.NeedSync)
                {
                    yield return (synchronizedObject, needSyncResult.EncodedSize);
                }
            }
        }

        public bool TryEncodeObjects(out List<byte[]> encodedObjectsBufferBatches)
        {
            IEnumerable<(ISynchronizedObject, int)> objectsToSync = GetObjectsToSync();

            if (objectsToSync.Count() == 0)
            {
                encodedObjectsBufferBatches = new List<byte[]>();
                return false;
            }

            List<BatchInfos> encodedObjectsBatches = new List<BatchInfos>()
            {
                new BatchInfos(new List<ISynchronizedObject>(), 0)
            };
            int currentBatchIndex = 0;
            foreach((ISynchronizedObject synchronizedObject, int encodedSize) in objectsToSync)
            {
                BatchInfos currentBatckInfos = encodedObjectsBatches[currentBatchIndex];
                if (currentBatckInfos.BatchSize + encodedSize > MAX_BATCH_SIZE)
                {
                    encodedObjectsBatches.Add(new BatchInfos(
                        new List<ISynchronizedObject>(){ synchronizedObject },
                        encodedSize));

                    currentBatchIndex++;
                }
                else
                {
                    currentBatckInfos.BatchSize += encodedSize;
                    currentBatckInfos.ObjectsToSync.Add(synchronizedObject);
                }
            }

            encodedObjectsBufferBatches = new List<byte[]>();
            foreach (BatchInfos batch in encodedObjectsBatches)
            {
                byte[] encodedObjectsBuffer = new byte[batch.BatchSize];
                int offset = 0;

                foreach (ISynchronizedObject synchronizedObject in batch.ObjectsToSync)
                {
                    synchronizedObject.PutEncodedObjectToBuffer(ref encodedObjectsBuffer, ref offset);
                }
                encodedObjectsBufferBatches.Add(encodedObjectsBuffer);
            }

            return true;
        }

        public void DecodeObjects(byte[] encodedObjects)
        {
            int offset = 0;
            while (offset < encodedObjects.Length)
            {
                int objectSize = EncodingUtility.Decode<int>(encodedObjects, ref offset);
                int initialOffset = offset;

                uint objectID = EncodingUtility.Decode<uint>(encodedObjects, ref offset);
                int objectDataSize = objectSize - sizeof(uint);

                if (m_synchronizedObjects.TryGetValue(objectID, out ISynchronizedObject synchronizedObject))
                {
                    synchronizedObject.DecodeObject(encodedObjects, ref offset, objectDataSize);
                    if (offset - initialOffset != objectSize)
                    {
                        Debug.LogError("Offset Overflow !");
                    }
                }
                else
                {
                    throw new InvalidDataException($"There are no object with ID {objectID}");
                }
            }
        }

        private IPAddress GetCurrentIP()
        {
            IPHostEntry hostEntry = Dns.GetHostEntry(Dns.GetHostName());
            IPAddress currentIpAddress = hostEntry.AddressList.FirstOrDefault(address => address.AddressFamily == AddressFamily.InterNetwork);
            return currentIpAddress;
        }

        private void OnGameStateChange(int obj)
        {
            OnGameStateChanged?.Invoke(obj);
        }
    }
}

