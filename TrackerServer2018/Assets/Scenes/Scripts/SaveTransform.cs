using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SaveTransform : MonoBehaviour
{
    public String saveKey = "";
    const char separator = ' ';
    String TransformtoString(Transform t)
    {
        string data = "";
        data += t.localPosition.x.ToString() + separator;
        data += t.localPosition.y.ToString() + separator;
        data += t.localPosition.z.ToString() + separator;
        data += t.localRotation.x.ToString() + separator;
        data += t.localRotation.y.ToString() + separator;
        data += t.localRotation.z.ToString() + separator;
        data += t.localRotation.w.ToString() + separator;
        data += t.localScale.x.ToString() + separator;
        data += t.localScale.y.ToString() + separator;
        data += t.localScale.z.ToString() + separator;
        return data;
    }
    void setTransformfromString(Transform t, String s)
    {
        String[] dataList = s.Split(separator);
        int index = 0;
        t.localPosition = new Vector3(
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]));
        t.localRotation = new Quaternion(
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]));
        t.localScale = new Vector3(
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]),
            float.Parse(dataList[index++]));
    }
    void Start()
    {
        setTransformfromString(transform, PlayerPrefs.GetString(saveKey));
    }
    void OnDestroy()
    {
        // スコアを保存
        PlayerPrefs.SetString(saveKey, TransformtoString(transform));
        PlayerPrefs.Save();
    }
}
