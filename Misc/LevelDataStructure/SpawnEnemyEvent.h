#include "IWaveEvent.h"

class SpawnEnemyEvent : public IWaveEvent
{
private:
    /* data */
public:
    SpawnEnemyEvent(/* args */);
    ~SpawnEnemyEvent();
    
    virtual void Load() override;
    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void OnWaveEnd() override;

    // Editor
    virtual void EditorLoad(float time) override;
    virtual void EditorUnload() override;

protected:
    virtual void OnFinish() override;
};

SpawnEnemyEvent::SpawnEnemyEvent(/* args */)
{
}

SpawnEnemyEvent::~SpawnEnemyEvent()
{
}

void SpawnEnemyEvent::Load()
{
    IWaveEvent::Load();
    // Request enemies from pool
}

void SpawnEnemyEvent::Start()
{
    IWaveEvent::Start();
    //Spawn the first one and start a timer to spawn the next ones
}

void SpawnEnemyEvent::Update(float deltaTime)
{
    IWaveEvent::Update(deltaTime);
    //Update the position of all spawned enemies
}

void SpawnEnemyEvent::OnWaveEnd()
{
    IWaveEvent::OnWaveEnd();
    //Release the enemies
}

void SpawnEnemyEvent::EditorLoad(float time)
{
    IWaveEvent::EditorLoad(time);
    // Display the spline

    if (time < GetTime())
    {
        // Display all enemies on the spline
    }
}

void SpawnEnemyEvent::EditorUnload()
{
    IWaveEvent::EditorUnload();
    //Unload all enemies
}

void SpawnEnemyEvent::OnFinish()
{
    IWaveEvent::OnFinish();
    //Do nothing maybe
}
