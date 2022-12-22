using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class SingletonMonoBehaviour<T> : MonoBehaviour, ISingleton<T> where T : SingletonMonoBehaviour<T>
{

}
