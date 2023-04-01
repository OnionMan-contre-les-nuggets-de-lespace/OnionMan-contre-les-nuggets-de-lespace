using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] private RectTransform[] possiblePlayerPoses;
    [SerializeField] private float horizontalSpeed;
    [SerializeField] private float verticalDownSpeed;
    [SerializeField] private float verticalUpSpeed;

    private bool doHorizontalMove;
    private bool doVerticalMove;
    private bool isAtDestination;

    private RectTransform playerRectTransform;
    private RectTransform playerTargetedPos;
    private RectTransform currentPlayerPos;

    private void Awake()
    {
        playerRectTransform = GetComponent<RectTransform>();
        playerRectTransform.position = possiblePlayerPoses[0].position;
        playerTargetedPos = possiblePlayerPoses[0];
        currentPlayerPos = possiblePlayerPoses[0];
    }

    public void GetPlayerTargetedPos(int i)
    {
        if(playerTargetedPos != possiblePlayerPoses[i])
        {
            doHorizontalMove = true;
            isAtDestination = false;
        }
        playerTargetedPos = possiblePlayerPoses[i];
        //playerRectTransform.position = possiblePlayerPoses[i].position;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.transform.CompareTag("Ladder") && playerRectTransform.position.y < playerTargetedPos.position.y)
        {
            doVerticalMove = true;
            doHorizontalMove = false;
        }
        if (collision.transform.CompareTag("Pole") && playerRectTransform.position.y > playerTargetedPos.position.y)
        {
            doVerticalMove = true;
            doHorizontalMove = false;
        }
    }

    private void HorizontalMove(int directionMultiplicator)
    {
        Vector2 tempPos = new Vector2(playerRectTransform.position.x + (horizontalSpeed * directionMultiplicator), playerRectTransform.position.y);
        playerRectTransform.position = tempPos;
    }

    private void VerticalUpMove()
    {
        Vector2 tempPos = new Vector2(playerRectTransform.position.x, playerRectTransform.position.y + verticalUpSpeed);
        playerRectTransform.position = tempPos;
    }

    private void VerticalDownMove()
    {
        Vector2 tempPos = new Vector2(playerRectTransform.position.x, playerRectTransform.position.y - verticalDownSpeed);
        playerRectTransform.position = tempPos;
    }

    private void Update()
    {
        //If player get to destination
        if(Vector2.Distance(playerRectTransform.position, playerTargetedPos.position) < 1)
        {
            currentPlayerPos = playerTargetedPos;
            doHorizontalMove = false;
            doVerticalMove = false;
            isAtDestination = true;
        }

        if (Mathf.Abs(playerTargetedPos.position.y - playerRectTransform.position.y) < 10)
        {
            doVerticalMove = false;

            if(!isAtDestination)
            {
                doHorizontalMove = true;
            }
        }

        if (Mathf.Abs(playerTargetedPos.position.x - playerRectTransform.position.x) < 10)
        {
            doHorizontalMove = false;
        }

        // Horizontal Movement
        if (doHorizontalMove)
        {
            if(playerRectTransform.position.x < playerTargetedPos.position.x)
            {
                doVerticalMove = false;
                HorizontalMove(1);
            }

            if(playerRectTransform.position.x > playerTargetedPos.position.x)
            {
                doVerticalMove = false;
                HorizontalMove(-1);
            }
        }

        //Vertical Movement
        if(doVerticalMove)
        {
            if(playerRectTransform.position.y < playerTargetedPos.position.y)
            {
                VerticalUpMove();
            }
            if (playerRectTransform.position.y > playerTargetedPos.position.y)
            {
                VerticalDownMove();
            }
        }
    }

}
