#pragma once
#include "Agent.h"

class Attacker: public Agent
{
public:
	Attacker();
	~Attacker();
	bool update();
	void init();
protected:
	bool attack;

};

