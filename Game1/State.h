#pragma once
#include "Graphics.h"	

class State {
protected:
	static Graphics* gfx;
	static HWND hwnd;
	double sec = 1.00;

public:

	static void Init(Graphics* graphics, HWND hw) {
		gfx = graphics;
		hwnd = hw;
	}

	bool loading;
	float Xpos, Ypos, syPos, sxPos;
	

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	
	virtual void Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) = 0;
};