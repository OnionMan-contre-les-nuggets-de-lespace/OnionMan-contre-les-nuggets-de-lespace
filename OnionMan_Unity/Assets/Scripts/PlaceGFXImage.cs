using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlaceGFXImage : MonoBehaviour
{
    [SerializeField] private List<Transform> ladders = new List<Transform>();
    [SerializeField] private List<RectTransform> laddersImage = new List<RectTransform>();
    [SerializeField] private Canvas mainCanvas;
    private void Start()
    {
        for(int i = 0; i < laddersImage.Count; i++)
        {
            RectTransform myRect = laddersImage[i];
            Vector2 myPositionOnScreen = Camera.main.WorldToScreenPoint(ladders[i].position);

            Canvas copyOfMainCanvas = mainCanvas;
            float scaleFactor = copyOfMainCanvas.scaleFactor;


            Vector2 finalPosition = new Vector2(myPositionOnScreen.x / scaleFactor, myPositionOnScreen.y / scaleFactor);
            myRect.anchoredPosition = finalPosition;

            //laddersImage[i].anchoredPosition = Camera.main.WorldToScreenPoint(ladders[i].position);
        }
    }
}
