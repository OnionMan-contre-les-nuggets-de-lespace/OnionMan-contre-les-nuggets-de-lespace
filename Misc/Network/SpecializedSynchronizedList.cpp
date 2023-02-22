#include "SpecializedSynchronizedList.h"

bool USpecializedSynchronizedList::NeedSync()
{
    CheckNeedSync();
    return m_needSync;
}