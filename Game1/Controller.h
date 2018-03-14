#pragma once
#include "State.h"
#include "Timer.h"

class Controller {

	Controller() {}
	static State* currentState;
	static Timer* timer;

public:
	static bool loading;
	static void Init();

	static void LoadInitialState(State* lev);
	static void SwitchState(State* lev);

	static void Render();
	
	//maybe add another update when you add input queue
	static void Update(std::vector<IA>* inputQue);
};