#pragma once
#include "MainScreen.h"	

void MainScreen::Load() {
	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	count = 0;
	selector = 0;

	setUpUIS();

}

void MainScreen::setUpUIS() {
	//the play,controls, and exit button
	//just going to have to manually guess the appropriate boxes for these texts, REEEEEE
	play = UI{ Hitbox{ { 250,300 },65,35 },hbZero,-1,true,true,FONTSIZE::MEDIUM,L"Play" };
	controls = UI{ Hitbox{{250,335},135,35},hbZero,-1,false,true,FONTSIZE::MEDIUM,L"Controls" };
	exit = UI{ Hitbox{ { 250,370 },65,35 },hbZero,-1,false,true,FONTSIZE::MEDIUM,L"Exit" };

	uis = new std::vector<UI>;
	uis->push_back(play);
	uis->push_back(controls);
	uis->push_back(exit);
}

void MainScreen::Unload() {
	//add stuff here
}

void MainScreen::Update(double timeTotal, double timeDelta, std::vector<IA>* inputQue) {
	if (count > 2) {
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		count = 0;
	}
	else {
		count += timeDelta;
	}

	//dealing with inputQue
	std::vector<IA> inputQ = *inputQue;
	for (auto& input : inputQ) {
		switch (input.action) {
		case KEY_DOWN:
			if (input.key == VK_UP) {
				if (selector != 0) {
					uis->at(selector).selected = false;
					selector--;
					uis->at(selector).selected = true;
				}
			}
			else if (input.key == VK_DOWN) {
				if (selector != (uis->size() - 1)) {
					uis->at(selector).selected = false;
					selector++;
					uis->at(selector).selected = true;
				}
				
			}
			else if (input.key == (VK_RETURN || VK_SPACE)) {
				switch (selector) {
				case 0:

					break;

				case 1:

					break;

				case 2:
					Unload();
					//find the correct way to exit the application (return to main)
					break;

				}
			}
			break;

		case KEY_RELEASE:

			break;

		default:

			break;
		}
				
	}
	inputQue->clear();
}

void MainScreen::Render() {
	gfx->ClearScreen(r, g, b);
	gfx->DrawUI(uis);
}