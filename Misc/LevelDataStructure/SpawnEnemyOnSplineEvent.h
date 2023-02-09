#include "SpawnEnemyEvent.h"

class SpawnEnemyOnSplineEvent : public SpawnEnemyEvent
{
private:
    USplineComponent* m_spline;
    
public:
    SpawnEnemyOnSplineEvent(/* args */);
    ~SpawnEnemyOnSplineEvent();

protected:

};

SpawnEnemyOnSplineEvent::SpawnEnemyOnSplineEvent(/* args */)
{
}

SpawnEnemyOnSplineEvent::~SpawnEnemyOnSplineEvent()
{
}
