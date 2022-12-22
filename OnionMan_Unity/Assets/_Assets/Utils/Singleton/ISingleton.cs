using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface ISingleton<T> where T : ISingleton<T>
{
    public static T Instance { get; }
}
