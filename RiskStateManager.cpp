#include "RiskStateManager.h"

void RiskStateManager::startNext()
{
	_currentPhase++;
}

int RiskStateManager::currentPhase()
{
	return _currentPhase;
}
