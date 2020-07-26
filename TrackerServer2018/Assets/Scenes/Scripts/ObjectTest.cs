using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectTest : MonoBehaviour
{
    public Sensor sensor;
    Quaternion basePose = Quaternion.identity;
	void Update()
    {
        if (sensor.quaternion != null)
        {
            transform.rotation = sensor.quaternion * Quaternion.Inverse(basePose);
			if (sensor.data.button)
			{
                basePose = sensor.quaternion;
            }
        }
    }
}
