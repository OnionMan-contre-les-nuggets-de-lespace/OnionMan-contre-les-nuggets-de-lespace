using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BunRoom : BaseRoom
{
    protected override void Start()
    {
        base.Start();
        roomManager.AddBunRoom(this);
    }
}
