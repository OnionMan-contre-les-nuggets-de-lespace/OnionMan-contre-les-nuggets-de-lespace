using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public interface IRoomAction
{
    bool CanBeDone { get; }

    void LaunchAction(RoomName roomName);

    string GetActionName();
}
