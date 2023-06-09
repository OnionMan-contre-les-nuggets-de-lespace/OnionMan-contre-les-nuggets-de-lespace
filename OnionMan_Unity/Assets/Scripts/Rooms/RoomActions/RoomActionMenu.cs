using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class RoomActionMenu : MonoBehaviour
{
    [SerializeField] private List<Button> m_actionButton = new List<Button>();
    [SerializeField] private CanvasGroup m_actionChoiceMenuCanvasGroup;
    [SerializeField] private List<TMP_Text> m_cantBeDoneFeedbackText = new List<TMP_Text>();


    private CanvasGroup canvasGroup;

    private void Awake()
    {
        canvasGroup = GetComponent<CanvasGroup>();
    }

    public void ShowActionMenu(List<RoomAction> actionList, BaseRoom roomToLaunchAction)
    {
        int indexOfFalseStament;
        for (int i = 0; i < actionList.Count; i++)
        {
            m_actionButton[i].gameObject.SetActive(true);
            m_cantBeDoneFeedbackText[i].gameObject.SetActive(true);
            m_actionButton[i].GetComponentInChildren<TMP_Text>().text = actionList[i].GetActionName();

            m_actionButton[i].interactable = actionList[i].CanBeDone(roomToLaunchAction, out indexOfFalseStament);
            //TODO : Rajouter un encart dynamique pour afficher une phrase de feedback quand on ne peut pas réaliser une action ("Vous avez l'extincteur/ Vous n'avez pas encore scanné de salles/etc...)

            if(actionList[i].CanBeDone(roomToLaunchAction, out indexOfFalseStament))
            {
                m_cantBeDoneFeedbackText[i].text = "L'action est disponible";
                int x = i;
                m_actionButton[i].onClick.AddListener(delegate { 
                    actionList[x].LaunchAction(roomToLaunchAction.roomName);
                    GameManager.DisablePlayerNavigation(true); //TODO : Reenable Navigation
                    HideAndResetActionMenu();
                });
            }
            else
            {
                m_cantBeDoneFeedbackText[i].text = "Action impossible : " + actionList[i].cantBeDoneFeedbackMessageList[indexOfFalseStament];
            }
        }
        m_actionChoiceMenuCanvasGroup.alpha = 1f;
        canvasGroup.interactable = true;
        canvasGroup.blocksRaycasts = true;
    }

    public void HideAndResetActionMenu()
    {
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
            entry.gameObject.SetActive(false);
        }


        //clickBlocker.SetActive(false);
    }
}
