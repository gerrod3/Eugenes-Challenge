#pragma once
#include "State.h"
//will include gameengine for update and render methods
//will include map

class FirstStage : public State {

	//Every level will have a Player object to host stats i think
	//Player player;
	//Map level;
	wchar_t* levelName;
	//will put the selector for escape screen into the game engine



public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) override;


};