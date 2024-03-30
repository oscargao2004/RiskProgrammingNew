#pragma once
class RiskStateManager
{
public:
	enum Phase
	{
		REINFORCEMENT = 0,
		ATTACK = 1,
		FORTIFICATION = 2
	};

	static void startNext();
	static void endTurn();
	static int currentPhase();

private:
	static int _currentPhase;

};

