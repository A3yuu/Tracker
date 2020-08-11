using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using UnityEngine.XR;

public class HMDPose : MonoBehaviour
{
    [DllImport("HMDPose")]
    private static extern int init();
    [DllImport("HMDPose")]
    private static extern void update();
    [DllImport("HMDPose")]
    private static extern float get(int i, int j);
    private void Start()
	{
        init();
	}
	void Update()
    {
        update();
        Matrix4x4 m = Matrix4x4.identity;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m[i, j] = get(i, j);
            }
        }
        m.m02 *= -1;
        m.m12 *= -1;
        m.m20 *= -1;
        m.m21 *= -1;
        m.m23 *= -1;
        transform.localPosition = new Vector3(m.m03, m.m13, m.m23);
        transform.localRotation = m.rotation;
    }
}