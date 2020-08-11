using System;
using UnityEngine;
using System.IO.MemoryMappedFiles;
using System.Text;
using System.IO;

public class SharedMemory : MonoBehaviour
{
    const String SharedMemoryKeyIn = "A3TrackerIn";
    const int SharedMemorySize = 1024;
    MemoryMappedFile mmfIn;
    MemoryMappedViewAccessor accessorIn;
    public Transform Hip;
    public Transform Left;
    public Transform Right;
    Matrix4x4 RL(Transform t)
    {
        //Matrix4x4 m = Matrix4x4.TRS(t.localPosition, t.localRotation, t.localScale);
        Matrix4x4 m = Matrix4x4.TRS(t.position, t.rotation, new Vector3(1, 1, 1));
        m.m02 *= -1;
        m.m12 *= -1;
        m.m20 *= -1;
        m.m21 *= -1;
        m.m23 *= -1;
        return m;
    }
    void Start()
    {
        mmfIn = MemoryMappedFile.CreateOrOpen(SharedMemoryKeyIn, SharedMemorySize);
        accessorIn = mmfIn.CreateViewAccessor(0, 0);
    }
    void MemoryStreamWriteTransform(MemoryStream ms, Matrix4x4 t)
	{
        ms.Write(BitConverter.GetBytes(t.m03), 0, 4);
        ms.Write(BitConverter.GetBytes(t.m13), 0, 4);
        ms.Write(BitConverter.GetBytes(t.m23), 0, 4);
        ms.Write(BitConverter.GetBytes(t.rotation.x), 0, 4);
        ms.Write(BitConverter.GetBytes(t.rotation.y), 0, 4);
        ms.Write(BitConverter.GetBytes(t.rotation.z), 0, 4);
        ms.Write(BitConverter.GetBytes(t.rotation.w), 0, 4);
    }
    void Update()
    {
        {
            
            MemoryStream ms = new MemoryStream();
            MemoryStreamWriteTransform(ms, RL(Hip));
            MemoryStreamWriteTransform(ms, RL(Left));
            MemoryStreamWriteTransform(ms, RL(Right));
            byte[] data = ms.ToArray();
            accessorIn.WriteArray(0, data, 0, data.Length);
		}
    }
}
