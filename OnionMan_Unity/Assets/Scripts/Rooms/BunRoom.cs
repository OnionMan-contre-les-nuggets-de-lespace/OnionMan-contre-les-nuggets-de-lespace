using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BunRoom : BaseRoom
{
    private void Start()
    {
        roomManager.AddBunRoom(this);
    }
}
