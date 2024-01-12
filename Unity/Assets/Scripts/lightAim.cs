using UnityEngine;

public class lightAim : MonoBehaviour
{
    public GameObject objectToSpawn;
    public Light lightSource;

    void Start()
    {
        // Instantiate the object
        GameObject spawnedObject = Instantiate(objectToSpawn, new Vector3(0, 0, 0), Quaternion.identity);

        // Create and configure the directional light
        GameObject lightGameObject = new GameObject("TheLight");
        Light lightComp = lightGameObject.AddComponent<Light>();
        lightComp.type = LightType.Directional;

        // Optional: Set other light properties
        lightComp.intensity = 1;
        lightComp.color = Color.white;

        // Point the light at the object
        lightGameObject.transform.rotation = Quaternion.LookRotation(spawnedObject.transform.position - lightGameObject.transform.position);
    
    }

    void PointLightAtObject(Transform target)
    {
        if (lightSource != null && target != null)
        {
            // Calculate the direction from the light to the target
            Vector3 directionToTarget = target.position - lightSource.transform.position;

            // Set the light's rotation to face the target
            lightSource.transform.rotation = Quaternion.LookRotation(directionToTarget);
        }
    }
}