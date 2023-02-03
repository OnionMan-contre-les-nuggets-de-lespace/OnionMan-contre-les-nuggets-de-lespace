using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiniGameManager : MonoBehaviour, IObserver
{
    private PlayerMovement playerMovement;

    private void OnEnable()
    {
        playerMovement = FindObjectOfType<PlayerMovement>();

        playerMovement.AddObserver(this);
    }

    private void OnDisable()
    {
        playerMovement.RemoveObserver(this);
    }

    public void OnNotify()
    {

    }
}
