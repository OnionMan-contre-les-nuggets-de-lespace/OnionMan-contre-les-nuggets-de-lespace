using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimatorController : MonoBehaviour
{
    private int m_isMovingId = Animator.StringToHash("isMoving");
    private int m_isClimbingId = Animator.StringToHash("isClimbing");
    private int m_isCraftingId = Animator.StringToHash("isCrafting");

    [SerializeField] private Animator _playerAnimator;

    public void EnterIdleAnimation()
    {
        _playerAnimator.SetBool(m_isMovingId, false);
    }

    public void EnterWalkAnimation()
    {
        _playerAnimator.SetBool(m_isMovingId, true);
        _playerAnimator.SetBool(m_isClimbingId, false);
    }
    public void EnterClimbAnimation()
    {
        _playerAnimator.SetBool(m_isClimbingId, true);
    }
    public void EnterCraftAnimation()
    {
        _playerAnimator.SetBool(m_isCraftingId, true);
    }

    public void ExitCraftAnimation()
    {
        _playerAnimator.SetBool(m_isCraftingId, false);
    }
}
