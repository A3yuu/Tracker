using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectTest : MonoBehaviour
{
    public Sensor sensor;
    void Update()
    {
        if (sensor.data != null)
        {
            //Vector3 data = sensor.data.Accel;
            //transform.rotation = Quaternion.FromToRotation(data, new Vector3(0, 0, -1));
            Vector3 data = sensor.data.Gyro * Time.deltaTime*0.1f;
            Quaternion rot = Quaternion.Euler(data);
            transform.rotation *= rot;
        }
    }
}
