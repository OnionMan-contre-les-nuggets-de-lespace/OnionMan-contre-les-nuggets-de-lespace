using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Linq;

using OnionMan.Utils;
using System.Net.Sockets;
using UnityEditor.Experimental.GraphView;
using UnityEngine.EventSystems;
using System.Threading;
using System;

namespace OnionMan.Network
{
    public class NetworkManager : SingletonMonoBehaviour<NetworkManager>
    {
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

        [SerializeField] private string m_ip;
        [SerializeField] private int m_port;

        private const int MAX_BATCH_SIZE = 8096;

        private Dictionary<uint, ISynchronizedObject> m_synchronizedObjects = new Dictionary<uint, ISynchronizedObject>();

        private TcpClient m_tcpClient;
        private NetworkStream m_networkStream;

        private int m_networkStreamOffset;

        Thread m_networkThread;

        private bool m_isConnected = false;
        private bool m_shouldListenForNetwork = false;

        public NetworkManager()
        {

        }

        protected virtual void LateUpdate()
        {
            if (m_isConnected)
            {
                if (TryEncodeObjects(out List<byte[]> encodedObjectsBatches))
                {
                    foreach (byte[] batch in encodedObjectsBatches)
                    {
                        m_networkStream.Write(batch);
                    }
                }
            }
        }

        public override void Initialize()
        {
            base.Initialize();
        }

        public void Connect()
        {
            if (!m_isConnected)
            {
                m_tcpClient = new TcpClient(m_ip, m_port);

                Debug.LogError($"Is Connected before connect: {m_tcpClient.Connected}");

                m_tcpClient.Connect(m_ip, m_port);

                Debug.LogError($"Is Connected after connect: {m_tcpClient.Connected}");

                m_networkStream = m_tcpClient.GetStream();
                m_isConnected = true;

                m_shouldListenForNetwork = true;
                m_networkThread = new Thread(new ThreadStart(ListenForNetwork));
            }
        }

        private void ListenForNetwork()
        {
            while (m_shouldListenForNetwork)
            {
                try
                {
                    byte[] encodedObjectsBuffer = new byte[MAX_BATCH_SIZE];
                    int encodedMessageSize = m_networkStream.Read(encodedObjectsBuffer, m_networkStreamOffset, MAX_BATCH_SIZE);

                    byte[] resizedEncodedObjects = new byte[encodedMessageSize];
                    EncodingUtility.ResizeBuffer(encodedObjectsBuffer, ref resizedEncodedObjects);

                    DecodeObjects(resizedEncodedObjects);
                }
                catch (ArgumentNullException e)
                {
                    Debug.LogException(e);
                }
                catch (SocketException e)
                {
                    Debug.LogException(e);
                }
                catch(Exception e)
                {
                    Debug.LogException(e);
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

        public bool TryEncodeObjects(out List<byte[]> encodedObjectsBufferBatch)
        {
            IEnumerable<(ISynchronizedObject, int)> objectsToSync = GetObjectsToSync();

            if (objectsToSync.Count() == 0)
            {
                encodedObjectsBufferBatch = new List<byte[]>();
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

            encodedObjectsBufferBatch = new List<byte[]>();
            foreach (BatchInfos batch in encodedObjectsBatches)
            {
                byte[] encodedObjectsBuffer = new byte[batch.BatchSize];
                int offset = 0;

                foreach (ISynchronizedObject synchronizedObject in batch.ObjectsToSync)
                {
                    synchronizedObject.PutEncodedObjectToBuffer(ref encodedObjectsBuffer, ref offset);
                }
                encodedObjectsBufferBatch.Add(encodedObjectsBuffer);
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
    }
}

