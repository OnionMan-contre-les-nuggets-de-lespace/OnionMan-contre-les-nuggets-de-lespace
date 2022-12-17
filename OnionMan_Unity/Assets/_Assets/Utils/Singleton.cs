using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Singleton<T> : MonoBehaviour where T : Singleton<T>, new()
{
    public static T Instance
    {
        get
        {
            if (m_instance == null)
            {
                m_instance= new T();
            }
            return m_instance;
        }
    }

    private static T m_instance;
}
