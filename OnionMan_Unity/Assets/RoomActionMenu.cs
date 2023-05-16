using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class RoomActionMenu : MonoBehaviour
{
    [SerializeField] private List<Button> m_actionButton = new List<Button>();

    private CanvasGroup canvasGroup;

    private void Awake()
    {
        canvasGroup = GetComponent<CanvasGroup>();
    }

    public void ShowActionMenu(List<IRoomAction> actionList)
    {
        for (int i = 0; i < actionList.Count; i++)
        {
            m_actionButton[i].gameObject.SetActive(true);
            m_actionButton[i].GetComponentInChildren<TMP_Text>().text = actionList[i].GetActionName();

            m_actionButton[i].interactable = actionList[i].CanBeDone;
            //TODO : Rajouter un encart dynamique pour afficher une phrase de feedback quand on ne peut pas réaliser une action ("Vous avez l'extincteur/ Vous n'avez pas encore scanné de salles/etc...)

            if(actionList[i].CanBeDone)
            {
                int x = i;
                m_actionButton[i].onClick.AddListener(delegate { actionList[x].LaunchAction(); });
            }
        }

        canvasGroup.alpha = 1f;
        canvasGroup.interactable = true;
        canvasGroup.blocksRaycasts = true;
    }

    public void HideActionMenu()
    {
        canvasGroup.blocksRaycasts = false;
        canvasGroup.interactable = false;
        canvasGroup.alpha = 0f;

        foreach (Button entry in m_actionButton)
        {
            entry.GetComponentInChildren<TMP_Text>().text = string.Empty;
            entry.onClick.RemoveAllListeners();
            entry.interactable = true;
            entry.gameObject.SetActive(false);
        }
    }
}
