using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class UpgradeManager : MonoBehaviour
{
    [SerializeField] private List<int> costOfWeaponUpgrade = new List<int>();
    [SerializeField] private TMP_Text numberOfScrappedPartText;
    [SerializeField] private SO_IndexOfCurrentWeapon SO_indexOfCurrentWeapon;



    public int numberOfScrappedPart;
    private int indexOfCurrentWeapon; //TODO : SynchronizedProperty

    public void UpgradeWeapon()
    {
        SO_indexOfCurrentWeapon.SP_IndexOfCurrentWeapon.Value++;
        //indexOfCurrentWeapon++;
        numberOfScrappedPart -= costOfWeaponUpgrade[SO_indexOfCurrentWeapon.SP_IndexOfCurrentWeapon.Value];
    }

    public bool NextUpgradeAvailable(out int costOfNextUpgrade)
    {
        costOfNextUpgrade = costOfWeaponUpgrade[SO_indexOfCurrentWeapon.SP_IndexOfCurrentWeapon.Value + 1];
        return costOfWeaponUpgrade[SO_indexOfCurrentWeapon.SP_IndexOfCurrentWeapon.Value + 1] <= numberOfScrappedPart;
    }

    public void UpdateScrappedPartCountText()
    {
        numberOfScrappedPartText.text = "Nombre de pièces détachées : " + numberOfScrappedPart.ToString();
    }
}
