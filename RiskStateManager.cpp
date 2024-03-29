#include "RiskStateManager.h"

void RiskStateManager::startNext()
{
	_currentPhase++;
}

void RiskStateManager::endTurn()
{
	_currentPhase = INITIAL;
}

int RiskStateManager::currentPhase()
{
	return _currentPhase;
}
