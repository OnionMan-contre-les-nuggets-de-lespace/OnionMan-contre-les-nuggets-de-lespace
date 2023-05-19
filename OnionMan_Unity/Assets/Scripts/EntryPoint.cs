using System.Collections;
using System.Collections.Generic;

using UnityEngine;
using UnityEngine.SceneManagement;

using OnionMan.Network;

public class EntryPoint : MonoBehaviour
{
    [SerializeField] private NetworkManager m_networkManagerPrefab;
    [SerializeField] private string m_mainMenuSceneName;

    // Start is called before the first frame update
    void Start()
    {
        NetworkManager networkManager = Instantiate(m_networkManagerPrefab);
        networkManager.name = nameof(NetworkManager);
        DontDestroyOnLoad(networkManager);
        NetworkManager.Instance.Initialize();

        Scene entryScene = SceneManager.GetActiveScene();
        SceneManager.LoadScene(m_mainMenuSceneName);
        //SceneManager.UnloadSceneAsync(entryScene);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
