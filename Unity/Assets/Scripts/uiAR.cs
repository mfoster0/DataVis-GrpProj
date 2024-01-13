using UnityEngine;
using UnityEngine.Video;
using UnityEngine.XR.ARFoundation;
using TMPro;

//Script need to be added to XROrigin, as it has ARPlaneManager and tapToPlace
public class uiAR : MonoBehaviour
{
    //Video player
    public VideoPlayer videoUX;
    //Video Clips
    public VideoClip v_UX;
    //Info texts
    
    // Events for found plane and content created
    private ARPlaneManager m_ARPlaneManager; //ARFoundation system
    private tapToPlace m_tapToPlace; //used to detect when the user create the content

    bool isContentVisible = false;

    // Start is called before the first frame update
    private void Awake()
    {
        videoUX.clip = v_UX;
        m_ARPlaneManager = GetComponent<ARPlaneManager>();
        m_ARPlaneManager.planesChanged += planeFound; //Subscribe to the event `plane is detected`

        m_tapToPlace = GetComponent<tapToPlace>();
        m_tapToPlace._contentVisibleEvent += contentVisible; //Subscribe to the event `content is created` (user Tap)
    }

    void planeFound(ARPlanesChangedEventArgs args)
    {
        //Plane found, turn off UI and Video
        //m_ARPlaneManager.planesChanged -= planeFound; //Unsubcribe

        if (isContentVisible)
        {   //Content created, turn off UI and Video
            videoUX.gameObject.SetActive(false);
            
        }

    }

    void contentVisible()
    {
        isContentVisible = true; //if the content is visible
        m_tapToPlace._contentVisibleEvent -= contentVisible; //Unsubscribe

        //Content created, turn off UI and Video
        videoUX.gameObject.SetActive(false);

    }
}