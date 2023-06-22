#include "SpawnEnemyEvent.h"

class SpawnEnemyAtPositionEvent : public SpawnEnemyEvent
{
private:


public:
    SpawnEnemyAtPositionEvent(/* args */);
    ~SpawnEnemyAtPositionEvent();

protected:
    virtual void SpawnEnemy() override;
};

SpawnEnemyAtPositionEvent::SpawnEnemyAtPositionEvent(/* args */)
{
}

SpawnEnemyAtPositionEvent::~SpawnEnemyAtPositionEvent()
{
}

inline void SpawnEnemyAtPositionEvent::SpawnEnemy()
{
}
