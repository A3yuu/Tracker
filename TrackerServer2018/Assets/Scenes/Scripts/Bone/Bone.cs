using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bone : MonoBehaviour
{
    public Sensor sensor;
    public Transform head;
    Quaternion basePose = Quaternion.identity;
    Quaternion rot = Quaternion.identity;
	void Update()
    {
        if (sensor.quaternion != null)
        {
            transform.rotation =  sensor.quaternion * Quaternion.Inverse(basePose) * rot;
            if (sensor.data.button)
            {
                //
                basePose = sensor.quaternion;
                //
                Vector3 p = head.rotation * new Vector3(0, 0, 1);
                p.y = 0;
                p = p.normalized;
                rot = Quaternion.FromToRotation(new Vector3(0, 0, 1), p);

            }
        }
    }
}
