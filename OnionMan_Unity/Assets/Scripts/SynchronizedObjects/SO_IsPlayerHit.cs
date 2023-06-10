using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_IsPlayerHit : SynchronizedMonoBehaviour
{
    public SynchronizedProperty<bool> isPlayerHit;
    public override void LoadProperties()
    {
        AddSynchronizedProperty(isPlayerHit);
    }
}
