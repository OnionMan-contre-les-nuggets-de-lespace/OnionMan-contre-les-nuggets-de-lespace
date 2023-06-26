using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using DG.Tweening;

public class RoomActionMenu : MonoBehaviour
{
    [SerializeField] private List<Button> m_actionButton = new List<Button>();
    [SerializeField] private CanvasGroup m_actionChoiceMenuCanvasGroup;
    [SerializeField] private List<TMP_Text> m_cantBeDoneFeedbackText = new List<TMP_Text>();
    [SerializeField] private Canvas mainCanvas;
    [SerializeField] private Slider actionTimeSlider;
    [SerializeField] private AudioSource clickAudioSource;

    [Space]
    [Header("DoTween ref")]
    [SerializeField] RectTransform panelTransform;
    [SerializeField] Vector2 minAnchorAnimEnd;
    [SerializeField] Vector2 maxAnchorAnimEnd;
    [SerializeField] Vector2 minAnchorAnimStart;
    [SerializeField] Vector2 maxAnchorAnimStart;


    private CanvasGroup canvasGroup;

    private void Awake()
    {
        canvasGroup = GetComponent<CanvasGroup>();
    }

    public void ShowActionMenu(List<RoomAction> actionList, BaseRoom roomToLaunchAction)
    {
        mainCanvas.sortingOrder = 15;
        Sequence seq = DOTween.Sequence();

        seq.Insert(0f, panelTransform.DOAnchorMin(minAnchorAnimEnd, .3f).From(minAnchorAnimStart).SetEase(Ease.OutBack));
        seq.Insert(0f, panelTransform.DOAnchorMax(maxAnchorAnimEnd, .3f).From(maxAnchorAnimStart).SetEase(Ease.OutBack));
        seq.Insert(0f, canvasGroup.DOFade(1f, .3f).From(0f).SetEase(Ease.OutCirc));

        seq.AppendCallback(() =>
        {
            ComputeActionsButton(actionList, roomToLaunchAction);
        });

        seq.Play();

        gameObject.SetActive(true);
    }

    private void ComputeActionsButton(List<RoomAction> actionList, BaseRoom roomToLaunchAction)
    {

        int indexOfFalseStament;
        for (int i = 0; i < actionList.Count; i++)
        {
            m_actionButton[i].gameObject.SetActive(true);
            m_cantBeDoneFeedbackText[i].transform.parent.gameObject.SetActive(true);
            m_actionButton[i].GetComponentInChildren<TMP_Text>().DOText(actionList[i].GetActionName(), 1.5f);
            //m_actionButton[i].GetComponentInChildren<TMP_Text>().text = actionList[i].GetActionName();

            m_actionButton[i].interactable = actionList[i].CanBeDone(roomToLaunchAction, out indexOfFalseStament);
            //TODO : Rajouter un encart dynamique pour afficher une phrase de feedback quand on ne peut pas réaliser une action ("Vous avez l'extincteur/ Vous n'avez pas encore scanné de salles/etc...)

            if (actionList[i].CanBeDone(roomToLaunchAction, out indexOfFalseStament))
            {
                m_cantBeDoneFeedbackText[i].DOText("L'action est disponible", 1f);
                //m_cantBeDoneFeedbackText[i].text = "L'action est disponible";
                int x = i;
                m_actionButton[i].onClick.AddListener(delegate {
                    clickAudioSource.Play();
                    HideAndResetActionMenu();
                    actionList[x].LaunchAction(roomToLaunchAction.roomName);
                    GameManager.DisablePlayerNavigation(true); //TODO : Reenable Navigation
                });
            }
            else
            {
                m_cantBeDoneFeedbackText[i].DOText("Action impossible : " + actionList[i].cantBeDoneFeedbackMessageList[indexOfFalseStament], 1f);
                //m_cantBeDoneFeedbackText[i].text = "Action impossible : " + actionList[i].cantBeDoneFeedbackMessageList[indexOfFalseStament];
            }
        }
        m_actionChoiceMenuCanvasGroup.alpha = 1f;
        canvasGroup.interactable = true;
        canvasGroup.blocksRaycasts = true;
    }


    public void HideAndResetActionMenu()
    {
        mainCanvas.sortingOrder = 0;
        canvasGroup.blocksRaycasts = false;
        canvasGroup.interactable = false;
        m_actionChoiceMenuCanvasGroup.alpha = 0f;

        foreach (Button entry in m_actionButton)
        {
            entry.GetComponentInChildren<TMP_Text>().text = string.Empty;
            entry.onClick.RemoveAllListeners();
            entry.interactable = true;
            entry.gameObject.SetActive(false);
        }

        foreach(TMP_Text entry in m_cantBeDoneFeedbackText)
        {
            entry.text = string.Empty;
            entry.transform.parent.gameObject.SetActive(false);
        }
    }

    IEnumerator TypingCoroutine(TMP_Text textToTypeIn, string textToType, float typingSpeed = 0.01f)
    {
        foreach(char c in textToType.ToCharArray())
        {
            textToTypeIn.text = textToType += c;
            yield return new WaitForSeconds(typingSpeed);
        }
    }

}
