using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiddleRoom : BaseRoom
{
    private void Start()
    {
        roomManager.AddMiddleRoom(this);
    }
}
