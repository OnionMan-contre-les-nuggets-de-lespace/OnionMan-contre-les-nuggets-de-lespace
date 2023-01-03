using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;
using System;

public class Test2 : SynchronizedMonoBehaviour
{
    [SerializeField]
    private SynchronizedProperty<Vector3> SP0;
    [SerializeField]
    private SynchronizedProperty<Quaternion> SP1;

    [SerializeField]
    private SynchronizedProperty<string> SP3;

    public override void LoadProperties()
    {
        AddSynchronizedProperty(SP0);
        AddSynchronizedProperty(SP1);
        AddSynchronizedProperty(SP3);
    }

    // Start is called before the first frame update
    protected override void Start()
    {
        SP0.OnValueChanged += OnSp0Changed;
    }

    private void OnSp2Changed(Quaternion obj)
    {
    }

    private void OnSp0Changed(Vector3 obj)
    {

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
