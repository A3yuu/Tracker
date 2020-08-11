using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AxlTest : MonoBehaviour
{
    public Sensor sensor;
    public int sensorNum = 0;
    //Vector3 accelSmooth;
    void Update()
    {
        if (sensor.data != null)
        {
            Vector3 accel = sensor.data.Accel;
            //accelSmooth = Vector3.Lerp(accelSmooth, accel, accelSmoothNum);
            //accel = accelSmooth;
            transform.localPosition = accel.normalized;
        }
    }
}
