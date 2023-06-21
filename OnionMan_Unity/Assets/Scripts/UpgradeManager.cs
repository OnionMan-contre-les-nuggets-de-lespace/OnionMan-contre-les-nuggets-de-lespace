using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class UpgradeManager : MonoBehaviour
{
    [SerializeField] private List<int> costOfWeaponUpgrade = new List<int>();
    [SerializeField] private TMP_Text numberOfScrappedPartText;



    public int numberOfScrappedPart;
    private int indexOfCurrentWeapon; //TODO : SynchronizedProperty

    public void UpgradeWeapon()
    {
        indexOfCurrentWeapon++;
        numberOfScrappedPart -= costOfWeaponUpgrade[indexOfCurrentWeapon];
    }

    public bool NextUpgradeAvailable(out int costOfNextUpgrade)
    {
        costOfNextUpgrade = costOfWeaponUpgrade[indexOfCurrentWeapon + 1];
        return costOfWeaponUpgrade[indexOfCurrentWeapon + 1] <= numberOfScrappedPart;
    }

    public void UpdateScrappedPartCountText()
    {
        numberOfScrappedPartText.text = "Nombre de pièces détachées : " + numberOfScrappedPart.ToString();
    }
}
