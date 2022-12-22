using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class SingletonScriptable<T> : ScriptableObject, ISingleton<T> where T : SingletonScriptable<T>
{

}
