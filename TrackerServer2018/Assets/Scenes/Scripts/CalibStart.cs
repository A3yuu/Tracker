using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CalibStart : MonoBehaviour
{
    public GameObject calib;
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            calib.SetActive(!calib.activeSelf);
        }
    }
}
