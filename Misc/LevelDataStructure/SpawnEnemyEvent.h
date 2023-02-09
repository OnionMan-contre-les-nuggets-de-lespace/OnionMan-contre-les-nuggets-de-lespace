#include "BaseWaveEvent.h"
#include "Components/SplineComponent.h"
#include "EnemyActor.h"

struct SpawnedEnnemy
{
private:
    AEnemyActor* m_enemyObject;
    float m_spawnTime;

public:
    SpawnedEnnemy(AEnemyActor* enemy, float spawnTime)
    {
        m_enemyObject = enemy;
        m_spawnTime = spawnTime;
    }

    AEnemyActor* Enemy() const
    {
        return m_enemyObject;
    }

    float SpawnTime() const
    {
        return m_spawnTime;
    }
};



class SpawnEnemyEvent : public BaseWaveEvent
{
private:
    AEnemyActor* m_enemyPrefab;
    
    int m_numberOfEnemiesToSpawn = 1;
    float m_timeBetweenSpawns = 0.0f;

    //Cache 
    TArray<SpawnedEnnemy> m_spawnedEnemies;

public:
    SpawnEnemyEvent(/* args */);
    ~SpawnEnemyEvent();
    
    virtual void Load(ULevelAsset* level) override;
    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void OnWaveEnd() override;

    // Editor
    virtual void EditorLoad(float time) override;
    virtual void EditorUnload() override;

protected:
    virtual void OnFinish() override;
    virtual void SpawnEnemy();

};

SpawnEnemyEvent::SpawnEnemyEvent(/* args */)
{
    
}

SpawnEnemyEvent::~SpawnEnemyEvent()
{
}

void SpawnEnemyEvent::Load(ULevelAsset* level)
{
    BaseWaveEvent::Load(level);
    m_spawnedEnemies.Reserve(sizeof(SpawnedEnnemy) * m_numberOfEnemiesToSpawn);
    // Request enemies from pool
}

void SpawnEnemyEvent::Start()
{
    BaseWaveEvent::Start();
    //Spawn the first one and start a timer to spawn the next ones
}

void SpawnEnemyEvent::Update(float deltaTime)
{
    BaseWaveEvent::Update(deltaTime);
    //Update the position of all spawned enemies
    for (SpawnedEnnemy spawned : m_spawnedEnemies)
    {
        if (spawned.Enemy()->IsAlive())
        {
            spawned.Enemy()->Move(m_levelAsset->CurrentWaveTime() - spawned.SpawnTime());
        }
    }
}

void SpawnEnemyEvent::OnWaveEnd()
{
    BaseWaveEvent::OnWaveEnd();
    //Release the enemies
}

void SpawnEnemyEvent::EditorLoad(float time)
{
    BaseWaveEvent::EditorLoad(time);
    // Display the spline

    if (time < GetTime())
    {
        // Display all enemies on the spline
    }
}

void SpawnEnemyEvent::EditorUnload()
{
    BaseWaveEvent::EditorUnload();
    //Unload all enemies and save the spline
}

void SpawnEnemyEvent::OnFinish()
{
    BaseWaveEvent::OnFinish();
    //Do nothing maybe
}

void SpawnEnemyEvent::SpawnEnemy()
{

}
