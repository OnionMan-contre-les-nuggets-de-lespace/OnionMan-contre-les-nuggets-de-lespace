using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    //[SerializeField] private RectTransform[] possiblePlayerPoses;
    [SerializeField] private Transform playerTransform;
    [SerializeField] private Transform[] possiblePlayerPoses;
    [SerializeField] private float horizontalSpeed;
    [SerializeField] private float verticalDownSpeed;
    [SerializeField] private float verticalUpSpeed;
    [SerializeField] private int startBurgerFloor;
    [Space]
    [Header("Raycast ref")]
    [SerializeField] private float checkDistance;
    [SerializeField] private LayerMask whatIsLadder;
    [SerializeField] private LayerMask whatIsPole;


    private bool doHorizontalMove;
    private bool doVerticalMove;
    private bool isAtDestination;

    private bool targetIsBelow;
    private bool targetIsAbove;
    private bool targetIsRight;
    private bool targetIsLeft;

    private bool playerIsAtTheRightFloor;

    //private RectTransform playerRectTransform;
    //private RectTransform playerTargetedPos;
    //private RectTransform currentPlayerPos;
    private Transform currentPlayerPos;
    private Transform playerTargetedPos;

    private RaycastHit2D[] sideCheckBuffer = new RaycastHit2D[1];

    public enum MovementDirection
    {
        RIGHT,
        LEFT,
        UP,
        DOWN,
        STAY
    }

    private MovementDirection movementDirection;

    #region Movement Sprite

    private void Awake()
    {
        playerTransform.position = possiblePlayerPoses[startBurgerFloor].position;
        playerTargetedPos = possiblePlayerPoses[startBurgerFloor];
        currentPlayerPos = possiblePlayerPoses[startBurgerFloor];
    }

    public void GetPlayerTargetedPos(int i)
    {
        //StopCoroutine(DoMoveCoroutine());
        if (playerTargetedPos != possiblePlayerPoses[i])
        {
            isAtDestination = false;

            playerTargetedPos = possiblePlayerPoses[i];
            targetIsAbove = playerTargetedPos.position.y > playerTransform.position.y;
            targetIsBelow = playerTargetedPos.position.y < playerTransform.position.y;
            targetIsLeft = playerTargetedPos.position.x > playerTransform.position.x;
            targetIsRight = playerTargetedPos.position.x < playerTransform.position.x;

            if(targetIsAbove)
            {
                if(LeftCheck(whatIsLadder))
                {
                    movementDirection = MovementDirection.LEFT;
                }
                else if(RightCheck(whatIsLadder))
                {
                    movementDirection = MovementDirection.RIGHT;
                }
            }

            if(targetIsBelow)
            {
                if (LeftCheck(whatIsPole))
                {
                    movementDirection = MovementDirection.LEFT;
                }
                else if (RightCheck(whatIsPole))
                {
                    movementDirection = MovementDirection.RIGHT;
                }
            }

            //StartCoroutine(DoMoveCoroutine());
            doHorizontalMove = true;
            isAtDestination = false;
        }
        //playerRectTransform.position = possiblePlayerPoses[i].position;
    }

    //IEnumerator DoMoveCoroutine()
    //{
    //    int left = -1;
    //    int right = 1;

    //    if(targetIsAbove)
    //    {
    //        if(LeftCheck(whatIsLadder))
    //        {
    //            while(Mathf.Abs(sideCheckBuffer[0].transform.position.x - playerTransform.position.x) > 0.1f)
    //            {
    //                HorizontalMove(left);
    //            }
    //        }

    //        if(RightCheck(whatIsLadder))
    //        {
    //            while (Mathf.Abs(sideCheckBuffer[0].transform.position.x - playerTransform.position.x) > 0.1f)
    //            {
    //                HorizontalMove(right);
    //            }
    //        }

    //        while (Mathf.Abs(playerTargetedPos.position.y - playerTransform.position.y) > 0.1f)
    //        {
    //            VerticalUpMove();
    //        }
    //    }

    //    if(targetIsBelow)
    //    {
    //        if (LeftCheck(whatIsPole))
    //        {
    //            while (Mathf.Abs(sideCheckBuffer[0].transform.position.x - playerTransform.position.x) > 0.1f)
    //            {
    //                HorizontalMove(left);
    //            }
    //        }

    //        if (RightCheck(whatIsPole))
    //        {
    //            while (Mathf.Abs(sideCheckBuffer[0].transform.position.x - playerTransform.position.x) > 0.1f)
    //            {
    //                HorizontalMove(right);
    //            }
    //        }

    //        while(Mathf.Abs(playerTargetedPos.position.y - playerTransform.position.y) > 0.1f)
    //        {
    //            VerticalDownMove();
    //        }
    //    }

    //    while (Mathf.Abs(playerTargetedPos.position.x - playerTransform.position.x) > 0.1f)
    //    {
    //        if (targetIsLeft)
    //        {
    //            HorizontalMove(left);
    //        }
    //        else if (targetIsRight)
    //        {
    //            HorizontalMove(right);
    //        }
    //    }

    //    yield return null;
    //}

    private void Update()
    {

        if(!isAtDestination)
        {
            int left = -1;
            int right = 1;

            switch (movementDirection)
            {
                case MovementDirection.LEFT:
                    HorizontalMove(left);
                    break;
                case MovementDirection.RIGHT:
                    HorizontalMove(right);
                    break;
                case MovementDirection.UP:
                    VerticalUpMove();
                    break;
                case MovementDirection.DOWN:
                    VerticalDownMove();
                    break;

            }


            if (Mathf.Abs(playerTargetedPos.position.y - playerTransform.position.y) < 0.1f) //Is a the right floor
            {
                if (playerTargetedPos.position.x > playerTransform.position.x)
                {
                    movementDirection = MovementDirection.RIGHT;
                }
                else if (playerTargetedPos.position.x < playerTransform.position.x)
                {
                    movementDirection = MovementDirection.LEFT;
                }
            }

            if(Vector2.Distance(playerTransform.position, playerTargetedPos.position) < 0.1f)
            {
                isAtDestination = true;
            }
        }
        



        //if (targetIsAbove)
        //{
        //    if (movementDirection == MovementDirection.LEFT)
        //    {
        //        HorizontalMove(left);
        //    }
        //    else if (movementDirection == MovementDirection.RIGHT)
        //    {
        //        HorizontalMove(right);
        //    }

        //    while (Mathf.Abs(playerTargetedPos.position.y - playerTransform.position.y) > 0.1f)
        //    {
        //        VerticalUpMove();
        //    }
        //}

        //if (targetIsBelow)
        //{
        //    if (LeftCheck(whatIsPole))
        //    {
        //        while (Mathf.Abs(sideCheckBuffer[0].transform.position.x - playerTransform.position.x) > 0.1f)
        //        {
        //            HorizontalMove(left);
        //        }
        //    }

        //    if (RightCheck(whatIsPole))
        //    {
        //        while (Mathf.Abs(sideCheckBuffer[0].transform.position.x - playerTransform.position.x) > 0.1f)
        //        {
        //            HorizontalMove(right);
        //        }
        //    }

        //    while (Mathf.Abs(playerTargetedPos.position.y - playerTransform.position.y) > 0.1f)
        //    {
        //        VerticalDownMove();
        //    }
        //}

        //while (Mathf.Abs(playerTargetedPos.position.x - playerTransform.position.x) > 0.1f)
        //{
        //    if (targetIsLeft)
        //    {
        //        HorizontalMove(left);
        //    }
        //    else if (targetIsRight)
        //    {
        //        HorizontalMove(right);
        //    }
        //}
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.transform.CompareTag("Ladder") && targetIsAbove)
        {
            movementDirection = MovementDirection.UP;
        }
        if (collision.transform.CompareTag("Pole") && targetIsBelow)
        {
            movementDirection = MovementDirection.DOWN;
        }
    }

    private void HorizontalMove(int directionMultiplicator)
    {
        Vector2 tempPos = new Vector2(playerTransform.position.x + (horizontalSpeed * directionMultiplicator), playerTransform.position.y);
        playerTransform.position = tempPos;
    }

    private void VerticalUpMove()
    {
        Vector2 tempPos = new Vector2(playerTransform.position.x, playerTransform.position.y + verticalUpSpeed);
        playerTransform.position = tempPos;
    }

    private void VerticalDownMove()
    {
        Vector2 tempPos = new Vector2(playerTransform.position.x, playerTransform.position.y - verticalDownSpeed);
        playerTransform.position = tempPos;
    }

    private bool LeftCheck(LayerMask whatToCheck)
    {
        int col = Physics2D.RaycastNonAlloc(playerTransform.position, Vector2.left, sideCheckBuffer, checkDistance, whatToCheck);

        return col > 0;
    }

    private bool RightCheck(LayerMask whatToCheck)
    {
        int col = Physics2D.RaycastNonAlloc(playerTransform.position, Vector2.right, sideCheckBuffer, checkDistance, whatToCheck);

        return col > 0;
    }



    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;

        Gizmos.DrawRay(playerTransform.position, Vector2.left * checkDistance);
        Gizmos.DrawRay(playerTransform.position, Vector2.right * checkDistance);

        if (LeftCheck(whatIsLadder))
        {
            //if (sideCheckBuffer[0].transform.CompareTag("Ladder"))
            //{
            //    Gizmos.color = Color.green;
            //}
            //else
            //{
            //    Gizmos.color = Color.blue;
            //}
            //Gizmos.DrawRay(playerTransform.position, Vector2.left * checkDistance);

            Gizmos.color = Color.green;

            Gizmos.DrawRay(playerTransform.position, Vector2.left * checkDistance);

        }

        if(RightCheck(whatIsLadder))
        {
            Gizmos.color = Color.green;

            Gizmos.DrawRay(playerTransform.position, Vector2.right * checkDistance);
        }

        if(LeftCheck(whatIsPole))
        {
            Gizmos.color = Color.blue;
            Gizmos.DrawRay(playerTransform.position, Vector2.left * checkDistance);
        }

        if(RightCheck(whatIsPole))
        {
            Gizmos.color = Color.blue;
            Gizmos.DrawRay(playerTransform.position, Vector2.right * checkDistance);
        }


        //if (RightCheck())
        //{
        //    if (sideCheckBuffer[0].transform.CompareTag("Ladder"))
        //    {
        //        Gizmos.color = Color.green;
        //    }
        //    else
        //    {
        //        Gizmos.color = Color.blue;
        //    }
        //    Gizmos.DrawRay(playerTransform.position, Vector2.right * checkDistance);
        //}
    }

    #endregion



    #region Movement Canvas UI Mode

    //private void Awake()
    //{
    //    playerRectTransform = GetComponent<RectTransform>();
    //    playerRectTransform.position = possiblePlayerPoses[0].position;
    //    playerTargetedPos = possiblePlayerPoses[0];
    //    currentPlayerPos = possiblePlayerPoses[0];
    //}

    //public void GetPlayerTargetedPos(int i)
    //{
    //    if(playerTargetedPos != possiblePlayerPoses[i])
    //    {
    //        doHorizontalMove = true;
    //        isAtDestination = false;
    //    }
    //    playerTargetedPos = possiblePlayerPoses[i];
    //    //playerRectTransform.position = possiblePlayerPoses[i].position;
    //}

    //private void OnTriggerEnter2D(Collider2D collision)
    //{
    //    if(collision.transform.CompareTag("Ladder") && playerRectTransform.position.y < playerTargetedPos.position.y)
    //    {
    //        doVerticalMove = true;
    //        doHorizontalMove = false;
    //    }
    //    if (collision.transform.CompareTag("Pole") && playerRectTransform.position.y > playerTargetedPos.position.y)
    //    {
    //        doVerticalMove = true;
    //        doHorizontalMove = false;
    //    }
    //}

    //private void HorizontalMove(int directionMultiplicator)
    //{
    //    Vector2 tempPos = new Vector2(playerRectTransform.position.x + (horizontalSpeed * directionMultiplicator), playerRectTransform.position.y);
    //    playerRectTransform.position = tempPos;
    //}

    //private void VerticalUpMove()
    //{
    //    Vector2 tempPos = new Vector2(playerRectTransform.position.x, playerRectTransform.position.y + verticalUpSpeed);
    //    playerRectTransform.position = tempPos;
    //}

    //private void VerticalDownMove()
    //{
    //    Vector2 tempPos = new Vector2(playerRectTransform.position.x, playerRectTransform.position.y - verticalDownSpeed);
    //    playerRectTransform.position = tempPos;
    //}

    //private void Update()
    //{
    //    //If player get to destination
    //    if(Vector2.Distance(playerRectTransform.position, playerTargetedPos.position) < 1)
    //    {
    //        currentPlayerPos = playerTargetedPos;
    //        doHorizontalMove = false;
    //        doVerticalMove = false;
    //        isAtDestination = true;
    //    }

    //    if (Mathf.Abs(playerTargetedPos.position.y - playerRectTransform.position.y) < 10)
    //    {
    //        doVerticalMove = false;

    //        if(!isAtDestination)
    //        {
    //            doHorizontalMove = true;
    //        }
    //    }

    //    if (Mathf.Abs(playerTargetedPos.position.x - playerRectTransform.position.x) < 10)
    //    {
    //        doHorizontalMove = false;
    //    }

    //    // Horizontal Movement
    //    if (doHorizontalMove)
    //    {
    //        if(playerRectTransform.position.x < playerTargetedPos.position.x)
    //        {
    //            doVerticalMove = false;
    //            HorizontalMove(1);
    //        }

    //        if(playerRectTransform.position.x > playerTargetedPos.position.x)
    //        {
    //            doVerticalMove = false;
    //            HorizontalMove(-1);
    //        }
    //    }

    //    //Vertical Movement
    //    if(doVerticalMove)
    //    {
    //        if(playerRectTransform.position.y < playerTargetedPos.position.y)
    //        {
    //            VerticalUpMove();
    //        }
    //        if (playerRectTransform.position.y > playerTargetedPos.position.y)
    //        {
    //            VerticalDownMove();
    //        }
    //    }
    //}

    #endregion

}
