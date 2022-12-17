using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;


namespace OnionMan.Network
{
    public class NetworkManager : Singleton<NetworkManager>
    {
        private List<ISynchronizedObject> m_synchronizedObjects = new List<ISynchronizedObject>();

        public NetworkManager()
        {

        }

        public void AddSynchronizedObject(ISynchronizedObject obj)
        {
            m_synchronizedObjects.Add(obj);
        }
    }
}

