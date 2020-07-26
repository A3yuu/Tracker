using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Neck : MonoBehaviour
{
    public Transform head;
    public Transform hip;
    void Update()
    {
        Quaternion rot = hip.rotation;
        transform.rotation = rot;
        hip.rotation = rot;
    }
}
