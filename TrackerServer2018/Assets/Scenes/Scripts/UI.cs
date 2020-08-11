using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityScript.Steps;

public class UI : MonoBehaviour
{
    const float scaleC = 0.1f;
    const int dataNum = 6;

    String[] saveKeys = {
        "NeckLen",
        "SpineLen",
        "HipLen",
        "HipWidth",
        "LegLen",
        "KneeLen",
    };
    const char separator = ' ';
    String saveKeysCOM = "COMNUM";

    InputField[] inputFields = new InputField[dataNum];
    public InputField NeckInput;
    public InputField SpineInput;
    public InputField HipInput;
    public InputField HipWidthInput;
    public InputField LegInput;
    public InputField KneeInput;

    public Transform Neck;
    public Transform Spine;
    public Transform Hip;
    public Transform LegL;
    public Transform LegR;
    public Transform KneeL;
    public Transform KneeR;
    public Transform FootL;
    public Transform FootR;

    public Transform NeckC;
    public Transform SpineC;
    public Transform HipC;
    public Transform HipWC;
    public Transform LegLC;
    public Transform LegRC;
    public Transform KneeLC;
    public Transform KneeRC;

    public SerialHandler serialHandler;
    public InputField InputCOM;

    float[] lens = new float[dataNum];
    const int NeckLen = 0;
    const int SpineLen = 1;
    const int HipLen = 2;
    const int HipWidthLen = 3;
    const int LegLen = 4;
    const int KneeLen = 5;

    void Start()
    {
        inputFields[0] = NeckInput;
        inputFields[1] = SpineInput;
        inputFields[2] = HipInput;
        inputFields[3] = HipWidthInput;
        inputFields[4] = LegInput;
        inputFields[5] = KneeInput;
        for (int i=0;i< dataNum; i++)
        {
            lens[i] = PlayerPrefs.GetFloat(saveKeys[i]);
            inputFields[i].text = lens[i].ToString();
        }
        InputCOM.text = PlayerPrefs.GetString(saveKeysCOM);
        serialHandler.portName = InputCOM.text;
    }
    public void setLength()
    {
        for (int i = 0; i < dataNum; i++)
        {
            lens[i] = float.Parse(inputFields[i].text);
            PlayerPrefs.SetFloat(saveKeys[i], lens[i]);
        }
        PlayerPrefs.Save();

        Neck.transform.localPosition = new Vector3(0, -lens[NeckLen], 0);
        Spine.transform.localPosition = new Vector3(0, -lens[SpineLen], 0);
        Hip.transform.localPosition = new Vector3(0, -lens[HipLen], 0);
        LegL.transform.localPosition = new Vector3(-lens[HipWidthLen] * 0.5f, 0, 0);
        LegR.transform.localPosition = new Vector3(lens[HipWidthLen] * 0.5f, 0, 0);
        KneeL.transform.localPosition = new Vector3(0, -lens[LegLen], 0);
        KneeR.transform.localPosition = new Vector3(0, -lens[LegLen], 0);
        FootL.transform.localPosition = new Vector3(0, -lens[KneeLen], 0);
        FootR.transform.localPosition = new Vector3(0, -lens[KneeLen], 0);

        NeckC.transform.localPosition = new Vector3(0, -lens[NeckLen] * 0.5f, 0);
        SpineC.transform.localPosition = new Vector3(0, -lens[SpineLen] * 0.5f, 0);
        HipC.transform.localPosition = new Vector3(0, -lens[HipLen] * 0.5f, 0);
        LegLC.transform.localPosition = new Vector3(0, -lens[LegLen] * 0.5f, 0);
        LegRC.transform.localPosition = new Vector3(0, -lens[LegLen] * 0.5f, 0);
        KneeLC.transform.localPosition = new Vector3(0, -lens[KneeLen] * 0.5f, 0);
        KneeRC.transform.localPosition = new Vector3(0, -lens[KneeLen] * 0.5f, 0);

        NeckC.transform.localScale = new Vector3(scaleC, lens[NeckLen] * 0.5f, scaleC);
        SpineC.transform.localScale = new Vector3(scaleC, lens[SpineLen] * 0.5f, scaleC);
        HipC.transform.localScale = new Vector3(scaleC, lens[HipLen] * 0.5f, scaleC);
        HipWC.transform.localScale = new Vector3(scaleC, lens[HipWidthLen] * 0.5f, scaleC);
        LegLC.transform.localScale = new Vector3(scaleC, lens[LegLen] * 0.5f, scaleC);
        LegRC.transform.localScale = new Vector3(scaleC, lens[LegLen] * 0.5f, scaleC);
        KneeLC.transform.localScale = new Vector3(scaleC, lens[KneeLen] * 0.5f, scaleC);
        KneeRC.transform.localScale = new Vector3(scaleC, lens[KneeLen] * 0.5f, scaleC);
    }
    public void setCOMNUM()
    {
        serialHandler.portName = InputCOM.text;
        PlayerPrefs.SetString(saveKeysCOM, InputCOM.text);
    }
}
