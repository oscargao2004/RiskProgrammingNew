#pragma once
class RiskStateManager
{
public:
	enum Phase
	{
		INITIAL = 0,
		REINFORCEMENT = 1,
		ATTACK = 2,
		FORTIFICATION = 3
	};

	static void startNext();
	static void endTurn();
	static int currentPhase();

private:
	static int _currentPhase;

};

