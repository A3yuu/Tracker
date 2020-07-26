using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MagCalib : MonoBehaviour
{
    public Sensor sensor;
    public GameObject spawnObject;
    public GameObject result;
    List<Vector3> points = new List<Vector3>();
    void Update()
    {
        if (sensor.data != null)
        {
            Debug.Log(sensor.data.ToString());
            Vector3 mag = sensor.data.Mag;
            points.Add(mag);
            GameObject obj = Instantiate(spawnObject, mag,new Quaternion());
            obj.transform.parent = transform;

            if (points.Count < 4) return;
            Matrix4x4 mat = Matrix4x4.zero;
            Vector4 vec = Vector4.zero;
            foreach (Vector3 point in points)
			{
                mat.m00 += 1;
                mat.m01 += point.x;
                mat.m02 += point.y;
                mat.m03 += point.z;

                mat.m11 += point.x* point.x;
                mat.m12 += point.x * point.y;
                mat.m13 += point.x * point.z;

                mat.m22 += point.y * point.y;
                mat.m23 += point.y * point.z;

                mat.m33 += point.z * point.z;
                float rho = (point.x * point.x) + (point.y * point.y) + (point.z * point.z);
                vec[0] += rho;
                vec[1] += rho * point.x;
                vec[2] += rho * point.y;
                vec[3] += rho * point.z;
            }
            mat.m10 = mat.m01;
            mat.m20 = mat.m02;
            mat.m21 = mat.m12;
            mat.m30 = mat.m03;
            mat.m31 = mat.m13;
            mat.m32 = mat.m23;

            Matrix4x4 matinv = mat.inverse;

            float r = 0;
            Vector3 c = Vector3.zero;
            for (int j = 0; j < 4; j++)
            {
                r += (matinv[0,j] * vec[j]);
                c.x += (matinv[1,j] * vec[j]);
                c.y += (matinv[2,j] * vec[j]);
                c.z += (matinv[3,j] * vec[j]);
            }
            r = Mathf.Sqrt(r + c.sqrMagnitude / 4.0f);
            c *= 0.5f;

            result.transform.localPosition = c;
            result.transform.localScale = new Vector3(r, r, r) * 2;
        }
    }
}
