using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace OnionMan.Utils
{
    public interface ISingleton<T> where T : ISingleton<T>
    {
        public static T Instance { get; }
    }
}
