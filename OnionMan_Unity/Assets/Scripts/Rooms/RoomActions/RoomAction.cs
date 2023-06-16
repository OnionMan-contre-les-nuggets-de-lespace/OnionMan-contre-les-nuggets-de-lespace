using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using DG.Tweening;
using UnityEngine.UI;

public class RoomAction : MonoBehaviour
{
    [SerializeField] protected string actionName;
    [SerializeField] public List<string> cantBeDoneFeedbackMessageList = new List<string>();
    [SerializeField] public float actionTime;

    protected RoomManager roomManager;
    protected PlayerAnimatorController playerAnimatorController;

    //public Action OnActionEnd;

    private void Start()
    {
        roomManager = FindObjectOfType<RoomManager>();
        playerAnimatorController = FindObjectOfType<PlayerAnimatorController>();
    }

    public virtual void LaunchAction(RoomName roomName)
    {
        playerAnimatorController.EnterCraftAnimation();
        ShowActionTimeSlider(roomName);
    }

    public virtual bool CanBeDone(BaseRoom baseRoom, out int indexOfFalseStatement)
    {
        indexOfFalseStatement = 0;
        return true;
    }

    public int GetFalseStatementIndex(List<bool> statement, out bool canBeDone)
    {
        int index = 0;
        canBeDone = true;
        for (int i = 0; i < statement.Count; i++)
        {
            if (!statement[i])
            {
                index = i;
                canBeDone = false;
                break;
            }
        }

        return index;
    }

    private void ShowActionTimeSlider(RoomName roomName)
    {
        Slider actionTimeSlider = roomManager.allRooms[roomName].actionTimeSlider;
        actionTimeSlider.gameObject.SetActive(true);
        Sequence seq = DOTween.Sequence();
        seq.Insert(0, actionTimeSlider.DOValue(0, actionTime));
        seq.AppendCallback(() =>
        {
            seq.Rewind();
            actionTimeSlider.gameObject.SetActive(false);
        });

        seq.Play();
    }

    public virtual string GetActionName()
    {
        return actionName;
    }
}
