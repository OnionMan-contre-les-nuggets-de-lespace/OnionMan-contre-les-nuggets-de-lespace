using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IRoomAction
{
    bool CanBeDone { get; }
    void LaunchAction();

    string GetActionName();
}
