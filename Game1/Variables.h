#pragma once


//All of my local variables I will want to use in my game engine 


//Inputs 
enum INPUTACTION {
	KEY_DOWN,
	KEY_RELEASE
};

//InputAction struct
struct IA
{
	INPUTACTION action;
	unsigned int key;
};

//Cord
struct Cord {
	float x;
	float y;
};

//Hitbox I'll make everything Top-Left based hitboxes
struct Hitbox {
	Cord cord;
	float width;
	float height;
};


#define hbZero Hitbox{{0,0},0,0}

enum FONTSIZE  {
	SMALL  = 20,
	MEDIUM  = 30,
	LARGE = 40
};

struct UI {
	Hitbox HB;
	Hitbox spriteHB;
	int bmID;
	bool selected;
	bool visible;
	FONTSIZE fontSize;
	wchar_t* uiName;
	
};
