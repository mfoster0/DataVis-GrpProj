using UnityEngine;
using System.Collections.Generic;
using System.Linq;
using Unity.XR.CoreUtils;
using TMPro;
using System;

public class mqttController : MonoBehaviour
{
    [Tooltip("Optional name for the controller")]
    public string nameController = "Ice Data Controller";
    public string tag_mqttManager = ""; //to be set on the Inspector panel. It must match one of the mqttManager.cs GameObject
    
    [Tooltip("the topic to subscribe must contain this value. !!Case Sensitive!! ")]
    public List<string> topicSubscribed = new List<string>(); //the topics to subscribe, these need to match a topic from the mqttManager
    private float topPointerValue = 0.0f;
    private float bottomPointerValue = 0.0f;
    private float lastTopPointerValue = 0.0f;
    private float lastBottomPointerValue = 0.0f;

    private string dataMonth = "";
    private string lastDataMonth = "";
    private string dataYear = "";
    private string lastDataYear = "";

    public GameObject dateDisplayObject;

    [Space]
    [Space]
    public GameObject topPointerObject; //pointer of the gauge, or other 3D models
    [Tooltip("Select the rotation axis of the object to control")]
    public enum State { X, Y, Z };
    public State topRotationAxis;
    [Space]
    [Tooltip("Direction Rotation")]
    public bool topCW = true; //CW True = 1; CW False = -1
    private int topRotationDirection = 1;
    [Space]
    [Space]
    [Tooltip("minimum value on the dial")]
    public float topStartValue = 0f; //start value of the gauge
    [Tooltip("maximum value on the dial")]
    public float topEndValue = 180f; // end value of the gauge
    [Tooltip("full extension of the gauge in EulerAngles")]
    public float topFullAngle = 180f; // full extension of the gauge in EulerAngles

    [Tooltip("Adjust the origin of the scale. negative values CCW; positive value CW")]
    public float topAdjustedStart = 0f; // negative values CCW; positive value CW
    [Space]
   
    [Space]
    public GameObject bottomPointerObject; //pointer of the gauge, or other 3D models
    [Tooltip("Select the rotation axis of the object to control")]
    public State bottomRotationAxis;
    [Space]
    [Tooltip("Direction Rotation")]
    public bool bottomCW = true; //CW True = 1; CW False = -1
    private int bottomRotationDirection = 1;
    [Space]
    [Space]
    [Tooltip("minimum value on the dial")]
    public float bottomStartValue = 0f; //start value of the gauge
    [Tooltip("maximum value on the dial")]
    public float bottomEndValue = 180f; // end value of the gauge
    [Tooltip("full extension of the gauge in EulerAngles")]
    public float bottomFullAngle = 180f; // full extension of the gauge in EulerAngles

    [Tooltip("Adjust the origin of the scale. negative values CCW; positive value CW")]
    public float bottomAdjustedStart = 0f; // negative values CCW; positive value CW
    [Space]

    public GameObject dailyNorthExentObject;
    private string dailyNEData = "";
    private string lastDailyNEData = "";
    public GameObject dailyNorthExentMeanObject;
    private string dailyNEMData = "";
    private string lastDailyNEMData = "";
    public GameObject dailyNorthPercChgObject;
    private string dailyNPCData = "";
    private string lastDailyNPCData = "";
    public GameObject dailySouthExentObject;
    private string dailySEData = "";
    private string lastDailySEData = "";
    public GameObject dailySouthExentMeanObject;
    private string dailySEMData = "";
    private string lastDailySEMData = "";
    public GameObject dailySouthPercChgObject;
    private string dailySPCData = "";
    private string lastDailySPCData = "";

    //the button at the top of the device to flip between daily and rolling data
    public GameObject DisplayedDataToggle;
    private int displayDaily = 0; //indicates daily and rolling data. 1 means daily data
    public mqttManager _eventSender;
    
    private bool dailyMode = false; //used to set the display mode of the gauges



    void Awake()
    {
        if (GameObject.FindGameObjectsWithTag(tag_mqttManager).Length > 0)
        {
            _eventSender = GameObject.FindGameObjectsWithTag(tag_mqttManager)[0].gameObject.GetComponent<mqttManager>();
            _eventSender.Connect(); //Connect tha Manager when the object is spawned
        }
        else
        {
            Debug.LogError("At least one GameObject with mqttManager component and Tag == tag_mqttManager needs to be provided");
        }
    }

    void OnEnable()
    {
        _eventSender.OnMessageArrived += OnMessageArrivedHandler;
        
    }

    private void OnDisable()
    {
        _eventSender.OnMessageArrived -= OnMessageArrivedHandler;
    }

    private void OnMessageArrivedHandler(mqttObj mqttObject) //the mqttObj is defined in the mqttManager.cs
    {

        //update values based on mqtt updates
        //if daily data is used, force an update as this data will not tick frequently
        if (topicSubscribed.Contains(mqttObject.topic.ToString()))
        {
            //Debug.Log("Topic in list");

            switch(mqttObject.topic) 
            {
                case "student/CASA0019/G6/data/north":
                    if (displayDaily == 0) 
                    {
                        topPointerValue = float.Parse(mqttObject.msg);
                    }
                    break;
                case "student/CASA0019/G6/data/south":
                    if (displayDaily == 0)
                    {
                        bottomPointerValue = float.Parse(mqttObject.msg);
                        //Debug.Log("Event Fired. The message, from Object " + nameController + " for bottom pointer is = " + bottomPointerValue);
                    }
                    break;
                case "student/CASA0019/G6/data/month":
                    if (displayDaily == 0)
                    {
                        dataMonth = mqttObject.msg.ToString();
                    }
                    else
                    {
                        dataMonth = DateTime.Now.ToString("MM");
                    }
                    break;
                case "student/CASA0019/G6/data/year":
                    if (displayDaily == 0)
                    {
                        dataYear = mqttObject.msg.ToString();
                    }
                    else
                    {
                        dataYear = DateTime.Now.Year.ToString();
                    }
                    break;    
                case "student/CASA0019/G6/data/northDailyExtent":
                    dailyNEData = mqttObject.msg.ToString();
                    if (displayDaily != 0)
                    {
                        topPointerValue = float.Parse(mqttObject.msg);
                    }
                    break;    
                case "student/CASA0019/G6/data/northDailyMean":
                    dailyNEMData = mqttObject.msg.ToString();
                    break;
                case "student/CASA0019/G6/data/northDailyExtentPercChange":
                    dailyNPCData = mqttObject.msg.ToString();
                    break; 
                case "student/CASA0019/G6/data/southDailyExtent":
                    dailySEData = mqttObject.msg.ToString();
                    if (displayDaily != 0)
                    {
                        bottomPointerValue = float.Parse(mqttObject.msg);
                    }                   
                    break;    
                case "student/CASA0019/G6/data/southDailyMean":
                    dailySEMData = mqttObject.msg.ToString();
                    break;
                case "student/CASA0019/G6/data/southDailyExtentPercChange":
                    dailySPCData = mqttObject.msg.ToString();
                    break; 
                case "student/CASA0019/G6/data/displayDaily":
                    displayDaily = int.Parse(mqttObject.msg);
                    
                    //if the data display has switched to daily, force update of the pointer values as this data is slow moving
                    //rolling data will update within 2 seconds
                    if (displayDaily != 0)
                    {
                        topPointerValue = float.Parse(dailyNEData);
                        bottomPointerValue = float.Parse(dailySEData);
                    }
                    break;
                default:
                    // do nothing
                    break;
            } 
                      
        }
        else
        {
            //Debug.Log("Topic doesn't match: " + mqttObject.topic);
        }
    }

    private void Update()
    {
        try
        {
            float step = 9.0f;
            
            if (topPointerValue != lastTopPointerValue)
            {
                topRotationDirection = topCW ? 1 : -1;

                Vector3 topRotationVector = new Vector3();
                //If the rotation Axis is X
                if (topRotationAxis == State.X)
                {
                    topRotationVector = new Vector3(
                    (topRotationDirection * ((topPointerValue - topStartValue) * (topFullAngle / (topEndValue - topStartValue)))) - topAdjustedStart,
                    topPointerObject.transform.localEulerAngles.y,
                    topPointerObject.transform.localEulerAngles.z);
                }
                //If the rotation Axis is Y
                else if (topRotationAxis == State.Y)
                {
                    topRotationVector = new Vector3(
                    topPointerObject.transform.localEulerAngles.x,
                    (topRotationDirection * ((topPointerValue - topStartValue) * (topFullAngle / (topEndValue - topStartValue)))) - topAdjustedStart,
                    topPointerObject.transform.localEulerAngles.z);

                }
                //If the rotation Axis is Z
                else if (topRotationAxis == State.Z)
                {
                    topRotationVector = new Vector3(
                    topPointerObject.transform.localEulerAngles.x,
                    topPointerObject.transform.localEulerAngles.y,
                    (topRotationDirection * ((topPointerValue - topStartValue) * (topFullAngle / (topEndValue - topStartValue)))) - topAdjustedStart);
                }
                topPointerObject.transform.localRotation = Quaternion.Lerp(
                        topPointerObject.transform.localRotation,
                        Quaternion.Euler(topRotationVector),
                        step);

                //capture value so only new values trigger an update        
                lastTopPointerValue = topPointerValue;
                Debug.Log("Updated top pointer: " + topPointerValue);
            }

            if (bottomPointerValue != lastBottomPointerValue)
            {
                bottomRotationDirection = bottomCW ? 1 : -1;

                Vector3 bottomRotationVector = new Vector3();
                //If the rotation Axis is X
                if (bottomRotationAxis == State.X)
                {
                    bottomRotationVector = new Vector3(
                    (bottomRotationDirection * ((bottomPointerValue - bottomStartValue) * (bottomFullAngle / (bottomEndValue - bottomStartValue)))) - bottomAdjustedStart,
                    bottomPointerObject.transform.localEulerAngles.y,
                    bottomPointerObject.transform.localEulerAngles.z);
                }
                //If the rotation Axis is Y
                else if (bottomRotationAxis == State.Y)
                {
                    bottomRotationVector = new Vector3(
                    bottomPointerObject.transform.localEulerAngles.x,
                    (bottomRotationDirection * ((bottomPointerValue - bottomStartValue) * (bottomFullAngle / (bottomEndValue - bottomStartValue)))) - bottomAdjustedStart,
                    bottomPointerObject.transform.localEulerAngles.z);

                }
                //If the rotation Axis is Z
                else if (bottomRotationAxis == State.Z)
                {
                    bottomRotationVector = new Vector3(
                    bottomPointerObject.transform.localEulerAngles.x,
                    bottomPointerObject.transform.localEulerAngles.y,
                    (bottomRotationDirection * ((bottomPointerValue - bottomStartValue) * (bottomFullAngle / (bottomEndValue - bottomStartValue)))) - bottomAdjustedStart);
                }
                bottomPointerObject.transform.localRotation = Quaternion.Lerp(
                        bottomPointerObject.transform.localRotation,
                        Quaternion.Euler(bottomRotationVector),
                        step);

                //capture value so only new values trigger an update        
                lastBottomPointerValue = bottomPointerValue;
                //Debug.Log("Updated bottom pointer: " + bottomPointerValue);
            }

            bool dateChanged = false;
            if (lastDataYear != dataYear)
            {
                dateChanged = true;
                lastDataYear = dataYear;
            }
            
            if (lastDataMonth != dataMonth)
            {
                dateChanged = true;
                lastDataMonth = dataMonth;
            }

            if (dateChanged)
            {
                dateDisplayObject.GetComponent<TextMeshProUGUI>().text = "Month    : " + dataMonth + "\n" + "Year     : " + dataYear;
            }

            if (lastDailyNEData != dailyNEData)
            {
                dailyNorthExentObject.GetComponent<TextMeshProUGUI>().text = dailyNEData;
                lastDailyNEData = dailyNEData;
            }
            if (lastDailyNEMData != dailyNEMData)
            {
                dailyNorthExentMeanObject.GetComponent<TextMeshProUGUI>().text = dailyNEMData;
                lastDailyNEMData = dailyNEMData;
            }
            if (lastDailyNPCData != dailyNPCData)
            {
                dailyNorthPercChgObject.GetComponent<TextMeshProUGUI>().text = dailyNPCData;
                lastDailyNPCData = dailyNPCData;
            }
            if (lastDailySEData != dailySEData)
            {
                dailySouthExentObject.GetComponent<TextMeshProUGUI>().text = dailySEData;
                lastDailySEData = dailySEData;
            }
            if (lastDailySEMData != dailySEMData)
            {
                dailySouthExentMeanObject.GetComponent<TextMeshProUGUI>().text = dailySEMData;
                lastDailySEMData = dailySEMData;
            }
            if (lastDailySPCData != dailySPCData)
            {
                dailySouthPercChgObject.GetComponent<TextMeshProUGUI>().text = dailySPCData;
                lastDailySPCData = dailySPCData;
            }
        }
        catch(Exception e)
        {
            Debug.Log("Error in 'Update': " + e.Message);
        }
    }
    
    
    private void PublishMessage(string topic, string message, bool retain)
    {
        _eventSender.retainMessage = retain;
        _eventSender.topicPublish = topic;
        _eventSender.messagePublish = message;
        _eventSender.Publish();
    }

    public void ToggleDataDisplayed()
    {
        string topic = "student/CASA0019/G6/data/displayDaily";
        string message = displayDaily == 0 ? "1" : "0"; //flip the displayDaily value - using ternary operator
        PublishMessage(topic, message, true);
    }
}