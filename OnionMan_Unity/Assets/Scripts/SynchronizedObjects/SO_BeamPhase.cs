using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OnionMan.Network;

public class SO_BeamPhase : SynchronizedMonoBehaviour
{
    [SerializeField] private SynchronizedProperty<bool> m_beamPhaseReady;
    [SerializeField] private SynchronizedProperty<bool> m_beamIsReady;
    public override void LoadProperties()
    {
        AddSynchronizedProperty(m_beamPhaseReady);
        AddSynchronizedProperty(m_beamIsReady);
    }
}
