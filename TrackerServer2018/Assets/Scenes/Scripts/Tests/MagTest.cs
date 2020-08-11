using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MagTest : MonoBehaviour
{
    public Sensor sensor;
    public Transform calibrateNum;
    //Vector3 magMax;
    // Vector3 magMin;
    void Update()
    {
        if (sensor.data != null)
        {
            Vector3 mag = sensor.data.Mag;
            mag = calibrateNum.InverseTransformPoint(mag);
            mag.x = -mag.x;
            //if (magMax.x < mag.x) magMax.x = mag.x;
            //if (magMax.y < mag.y) magMax.y = mag.y;
            //if (magMax.z < mag.z) magMax.z = mag.z;
            //if (magMin.x > mag.x) magMin.x = mag.x;
            //if (magMin.y > mag.y) magMin.y = mag.y;
            //if (magMin.z > mag.z) magMin.z = mag.z;
            //mag -= magMax - magMin;
            //mag.x = (mag.x - magMin.x) / (magMax.x - magMin.x) - 0.5f;
            //mag.y = (mag.y - magMin.y) / (magMax.y - magMin.y) - 0.5f;
            //mag.z = (mag.z - magMin.z) / (magMax.z - magMin.z) - 0.5f;
            transform.localPosition = mag;
        }
    }
}
