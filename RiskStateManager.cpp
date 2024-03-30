#include "RiskStateManager.h"

int RiskStateManager::_currentPhase = 0;

void RiskStateManager::startNext()
{
	_currentPhase++;
}

void RiskStateManager::endTurn()
{
	_currentPhase = REINFORCEMENT;
}

int RiskStateManager::currentPhase()
{
	return _currentPhase;
}
