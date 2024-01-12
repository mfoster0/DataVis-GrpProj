using UnityEngine;
using TMPro;
using UnityEngine.UI;

public class DisplayData : MonoBehaviour
{
    //public TextMeshProUGUI labelToUpdate;
    public GameObject heatmapObj;
    public GameObject extentInfoObj;
    public GameObject arcticImage;
    public GameObject antarcticImage;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    public void displayArctic()
    {
        displayInfo(0);
    }
    public void displayAntarctic()
    {
       displayInfo(1);
    }
    public void displayHeatmap()
    {
         displayInfo(2);
    }

    public void displayExtentInfo()
    {
       displayInfo(3);
    }

    private void displayInfo(int itemToDisplay)
    {
        switch(itemToDisplay) 
        {
            case 0:
                // display Arctic
                antarcticImage.SetActive(false);
                heatmapObj.SetActive(false);
                extentInfoObj.SetActive(false);
                arcticImage.SetActive(!arcticImage.activeSelf); // Toggle the visibility of the image
                break;
            case 1:
                // display antarctic
                arcticImage.SetActive(false);
                heatmapObj.SetActive(false);
                extentInfoObj.SetActive(false);
                antarcticImage.SetActive(!antarcticImage.activeSelf); // Toggle the visibility of the image
                break;
            case 2:
                // display trend data
                antarcticImage.SetActive(false);
                arcticImage.SetActive(false);
                extentInfoObj.SetActive(false);    
                heatmapObj.SetActive(!heatmapObj.activeSelf); // Toggle the visibility of the image  
                break;
            case 3:
                // display supplemental data
                antarcticImage.SetActive(false);
                arcticImage.SetActive(false);
                heatmapObj.SetActive(false);
                extentInfoObj.SetActive(!extentInfoObj.activeSelf); // Toggle the visibility of the image
                break;    
            default:
                break;
        } 
    }
}
