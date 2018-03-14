#include "State.h"

class MainScreen : public State {

	//this is the name of the sprite sheet for the graphics initialation, might make into a vector
	wchar_t* spriteSheet;
	float r, g, b;
	float width, height;
	double count;
	int selector;
	//POINT mousePosition;
	
	//UIS
	UI play, controls, exit;
	std::vector<UI>* uis;


public:
	void Load() override;
	void Unload() override;
	void Render() override;
	//will have another update method for game input
	
	void Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) override;

	void setUpUIS();

};