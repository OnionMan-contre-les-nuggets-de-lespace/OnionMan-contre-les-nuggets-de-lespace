using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiniGameManager : MonoBehaviour, IObserver
{
    private PlayerMovement playerMovement;
    private bool hasWinMiniGame;
    private bool hasLooseMiniGame;


    [SerializeField] private GameObject miniGameGameObject;

    private void Awake()
    {
        hasWinMiniGame = false;
        hasLooseMiniGame = false;
        miniGameGameObject.SetActive(false);
    }

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
        miniGameGameObject.SetActive(true);
    }

    public void OC_WinMinigame()
    {
        hasWinMiniGame = true;
        miniGameGameObject.SetActive(false);
    }

    public void OC_LooseMinigame()
    {
        hasLooseMiniGame = true;
        miniGameGameObject.SetActive(false);
    }
}
