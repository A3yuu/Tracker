using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SensorData
{
    public Vector3 Accel, Gyro, Mag;
    public SensorData(String data)
    {
        String[] strs = data.Split(' ');
        Accel.x = float.Parse(strs[0]);
        Accel.y = float.Parse(strs[1]);
        Accel.z = float.Parse(strs[2]);
        Gyro.x = float.Parse(strs[3]);
        Gyro.y = float.Parse(strs[4]);
        Gyro.z = float.Parse(strs[5]);
        Mag.x = float.Parse(strs[6]);
        Mag.y = float.Parse(strs[7]);
        Mag.z = float.Parse(strs[8]);
    }
    public override String ToString()
    {
        return
            Accel.x + " " +
            Accel.y + " " +
            Accel.z + " " +
            Gyro.x + " " +
            Gyro.y + " " +
            Gyro.z + " " +
            Mag.x + " " +
            Mag.y + " " +
            Mag.z;
    }
};
public class Sensor : MonoBehaviour
{
    public SerialHandler serialHandler;
    public SensorData data;

    void Start()
    {
        //信号を受信したときに、そのメッセージの処理を行う
        serialHandler.OnDataReceived += OnDataReceived;
    }

    //受信した信号(message)に対する処理
    void OnDataReceived(string message)
    {
        try
        {
            data = new SensorData(message);
            //Debug.Log(data);
        }
        catch (System.Exception e)
        {
            Debug.LogWarning(e.Message);
        }
    }
}