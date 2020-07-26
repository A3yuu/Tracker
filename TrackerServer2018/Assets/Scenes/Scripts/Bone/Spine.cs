using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spine : MonoBehaviour
{
    public Transform neck;
    public Transform hip;
    public float rate = 0.5f;
    void Update()
    {
        Quaternion rot = hip.rotation;
        transform.rotation = Quaternion.Slerp(neck.rotation, rot, rate);
        hip.rotation = rot;

    }
}
