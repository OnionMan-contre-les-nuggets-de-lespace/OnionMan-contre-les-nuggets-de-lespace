using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Linq;

namespace OnionMan.Network
{
    public class NetworkManager : Singleton<NetworkManager>
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

        public IEnumerable<ISynchronizedObject> GetObjectsToSync()
        {
            foreach (ISynchronizedObject synchronizedObject in m_synchronizedObjects.Values)
            {
                if (synchronizedObject.NeedSynchronization)
                {
                    yield return synchronizedObject;
                }
            }
        }

        public byte[] EncodeObjectsToSync()
        {
            IEnumerable<byte> encodedObjects = new byte[0];
            foreach(ISynchronizedObject synchronizedObject in GetObjectsToSync())
            {
                synchronizedObject.NeedSynchronization = false;
                IEnumerable<byte> encodedObject = 
                    EncodingUtility.Encode(synchronizedObject.ObjectID)
                    .Concat(synchronizedObject.GetEncodedProperties());

                encodedObjects = encodedObjects.Concat(
                    EncodingUtility.Encode(encodedObject.Count())
                    .Concat(encodedObject));

                Debug.LogError($"Encoded Object : {EncodingUtility.GetBytesAsString(encodedObject)}");
            }
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
                if (m_synchronizedObjects.TryGetValue(objectID, out ISynchronizedObject synchronizedObject))
                {
                    synchronizedObject.DecodeProperties(encodedObjects, ref offset);
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

