/// <summary>
/// Singleton pour les scriptable objects
/// </summary>

using UnityEngine;

namespace OnionMan.Utils
{
    public abstract class SingletonScriptable<T> : ScriptableObject, ISingleton<T> where T : SingletonScriptable<T>
    {
        private static T s_instance = default(T);

        public static T Instance
        {
            get
            {
                Load();
                return s_instance;
            }
        }

        public static void Load()
        {
            if (s_instance == null)
            {
                string classname = typeof(T).ToString();
                s_instance = Resources.Load<T>(classname);
            }
        }
    }
}
