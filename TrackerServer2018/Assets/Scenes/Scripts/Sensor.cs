using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
public class SensorData
{
    public uint time;
    public bool button;
    public Vector3 Accel, Gyro, Mag;
    const int sensorDataNum = 9;
    public SensorData(String data, int sensorNum = 0)
    {
        String[] strs = data.Split(' ');
        time = uint.Parse(strs[0]);
        button = int.Parse(strs[1]) == 0;
        Accel.x = float.Parse(strs[2 + sensorNum * sensorDataNum]);
        Accel.y = float.Parse(strs[3 + sensorNum * sensorDataNum]);
        Accel.z = float.Parse(strs[4 + sensorNum * sensorDataNum]);
        Gyro.x = float.Parse(strs[5 + sensorNum * sensorDataNum]);
        Gyro.y = float.Parse(strs[6 + sensorNum * sensorDataNum]);
        Gyro.z = float.Parse(strs[7 + sensorNum * sensorDataNum]);
        Mag.x = float.Parse(strs[8 + sensorNum * sensorDataNum]);
        Mag.y = float.Parse(strs[9 + sensorNum * sensorDataNum]);
        Mag.z = float.Parse(strs[10 + sensorNum * sensorDataNum]);
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
            Mag.z +" " +
            time + " " +
            button;
    }
};
public class Sensor : MonoBehaviour
{
    public int sensorNum = 0;

    public SerialHandler serialHandler;
    public SensorData data;
    public Quaternion quaternion { get; private set; } = Quaternion.identity;

    double oldTime = 0;

    public Transform magCalibrateNum;
    Vector3 magCalibratePos;
    public const float gyroSpeedRate = 0.2f;
    public const float gyroRate = 0.5f;
    public const float accelSmoothNum = 0.3f;
    Vector3 accelSmooth;
    public const float smoothNum = 0.3f;
    Quaternion smooth;
    Quaternion oldQuaternion = Quaternion.identity;
    int allSmoothNum = 32;
    List<double> times = new List<double>();
    List<Quaternion> quaternions = new List<Quaternion>();

    void Start()
    {
        serialHandler.OnDataReceived += OnDataReceived;
        magCalibratePos = magCalibrateNum.position;
    }
    void OnDataReceived(string message)
    {
        try
        {
            data = new SensorData(message, sensorNum);
            Debug.Log(data.ToString());

            //磁力取得
            Vector3 mag = data.Mag;
            //キャリブレーション
            //mag = magCalibrateNum.InverseTransformPoint(mag);
            mag -= magCalibratePos;
            //磁力平滑化
            //magSmooth = Vector3.Lerp(magSmooth, mag, magSmoothNum);
            //mag = magSmooth;

            //加速度取得
            Vector3 accel = data.Accel;
            //加速度平滑化
            accelSmooth = Vector3.Lerp(accelSmooth, accel, accelSmoothNum);
            accel = accelSmooth;
            accel = accel.normalized;
            //磁力方向補正
            mag -= Vector3.Dot(accel, mag) * accel;
            mag = mag.normalized;

            //ベース作成
            //加速度
            Quaternion accelQ = Quaternion.FromToRotation(accel, new Vector3(0, 1, 0));
            //磁力
            Vector3 acceledMag = accelQ * mag;
            Quaternion magQ = Quaternion.FromToRotation(acceledMag, new Vector3(0, 0, -1));
            //ジャイロ
            double nowTime = data.time * 1e-3;
            double pastTime = nowTime - oldTime;
            Vector3 gyro = data.Gyro * (float)pastTime;
            oldTime = nowTime;
            Quaternion rot = Quaternion.Euler(-gyro);
            float angle = Quaternion.Angle(Quaternion.identity, rot);
            Quaternion q = Quaternion.Slerp(magQ * accelQ, oldQuaternion * rot, angle * gyroSpeedRate + gyroRate).normalized;
            if (float.IsNaN(q.x)) q = Quaternion.identity;

            //最終平滑
            //smooth = Quaternion.Slerp(smooth, q, smoothNum);
            //if (float.IsNaN(smooth.x)) smooth = new Quaternion();
            //quaternion = smooth;

            //最小二乗法
            quaternions.Add(q * Quaternion.Inverse(oldQuaternion));
            times.Add(pastTime);
            if (quaternions.Count > allSmoothNum) quaternions.RemoveRange(0, quaternions.Count - allSmoothNum);
            if (times.Count > allSmoothNum) times.RemoveRange(0, times.Count - allSmoothNum);
            int nowCount = quaternions.Count;
            //x平均
            double ux = times.Average();
            //y平均
            Quaternion uy = Quaternion.identity;
            foreach (Quaternion y in quaternions)
            {
                uy *= Quaternion.SlerpUnclamped(Quaternion.identity, y, 1.0f / nowCount);
            }
            //uy = Quaternion.SlerpUnclamped(Quaternion.identity, uy, 1.0f / allSmoothNum);
            Quaternion uyInv = Quaternion.Inverse(uy);
            //x分散
            double sx = 0;
            foreach (double y in times)
            {
                double s = y - ux;
                sx += s * s;
            }
            sx /= nowCount;
            //共分散
            Quaternion kbs = Quaternion.identity;
            for (int i = 0; i < nowCount; i++)
            {
                kbs *= Quaternion.SlerpUnclamped(Quaternion.identity, quaternions[i] * uyInv, (float)(times[i] - ux));
            }
            kbs = Quaternion.SlerpUnclamped(Quaternion.identity, kbs, 1.0f / nowCount);
            //kbs = Quaternion.SlerpUnclamped(Quaternion.identity, kbs, (float)((times[nowCount - 1] - ux) / sx / nowCount));
            kbs = Quaternion.SlerpUnclamped(Quaternion.identity, kbs, (float)((times[nowCount - 1] - ux) / sx)) * uy;
            quaternion = Quaternion.Slerp((kbs * quaternion).normalized, q, 0.01f);
            if (float.IsNaN(quaternion.x)) quaternion = Quaternion.identity;
            //
            oldQuaternion = q;
        }
        catch (Exception e)
        {
            Debug.LogWarning(e.Message);
        }
    }
};