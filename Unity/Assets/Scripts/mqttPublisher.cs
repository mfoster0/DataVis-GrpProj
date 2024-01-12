using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class mqttPublisher : MonoBehaviour
{
    public mqttController _mqttController;
    
    [Tooltip("Optional name for the data publisher")]
    public string nameController = "Ice Data Publisher";
    public string tag_mqttController = ""; //to be set on the Inspector panel. It must match one of the mqttController.cs GameObject

    void Awake()
    {
        
        if (GameObject.FindGameObjectsWithTag(tag_mqttController).Length > 0)
        {
            //get the mqttController instance used
            _mqttController = GameObject.FindGameObjectsWithTag(tag_mqttController)[0].gameObject.GetComponent<mqttController>();
            Debug.Log("mqttPublish controller object name: " + _mqttController.name);
        }
        else
        {
            Debug.LogError("At least one GameObject with mqttController component and Tag == tag_mqttController needs to be provided");
        }
        
    }


    public void SwitchData()
    {
        Debug.Log("In mqttPublisher::SwitchData");

        _mqttController.ToggleDataDisplayed();
        return;

    }
    

}