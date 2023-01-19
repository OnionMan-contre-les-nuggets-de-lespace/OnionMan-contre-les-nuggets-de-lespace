using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Linq;

using OnionMan.Utils;

namespace OnionMan.Network
{
    public class NetworkManager : SingletonMonoBehaviour<NetworkManager>
    {
        private Dictionary<uint, ISynchronizedObject> m_synchronizedObjects = new Dictionary<uint, ISynchronizedObject>();

        public NetworkManager()
        {

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

        public byte[] EncodeObjects()
        {
            IEnumerable<(ISynchronizedObject, int)> objectsToSync = GetObjectsToSync();

            int encodedObjectsTotalSize = 0;
            foreach((ISynchronizedObject synchronizedObject, int encodedSize) in objectsToSync)
            {
                encodedObjectsTotalSize += encodedSize;
            }

            IEnumerable<byte> encodedObjects = new byte[encodedObjectsTotalSize];
            int offset = 0;

            foreach ((ISynchronizedObject synchronizedObject, int encodedSize) in objectsToSync)
            {
                synchronizedObject.PutEncodedObjectToBuffer(encodedObjects, ref int offset);
            }

            encodedObjects = encodedObjects.Concat(synchronizedObject.EncodeObject());
            return encodedObjects.ToArray();
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

