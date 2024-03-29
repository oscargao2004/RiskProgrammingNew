#pragma once
class RiskStateManager
{
private:
	static int _currentPhase;
public:
	enum Phase
	{
		INITIAL = 0,
		FORTIFICATION = 1,
		ATTACK = 2,
		REINFORCEMENT = 3
	};

	static void startNext();
	static int currentPhase();


};

