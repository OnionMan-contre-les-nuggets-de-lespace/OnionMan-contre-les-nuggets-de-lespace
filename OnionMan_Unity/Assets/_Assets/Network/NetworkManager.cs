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

        public IEnumerable<ISynchronizedObject> GetObjectsToSync()
        {
            foreach (ISynchronizedObject synchronizedObject in m_synchronizedObjects.Values)
            {
                if (synchronizedObject.NeedSync)
                {
                    yield return synchronizedObject;
                }
            }
        }

        public byte[] EncodeObjects()
        {
            IEnumerable<byte> encodedObjects = new byte[0];
            foreach(ISynchronizedObject synchronizedObject in GetObjectsToSync())
            {
                encodedObjects = encodedObjects.Concat(synchronizedObject.EncodeObject());
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

