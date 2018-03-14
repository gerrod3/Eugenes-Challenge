#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#include <vector>
#include "Variables.h"


class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	IDWriteTextFormat* textFormat;
	IDWriteFactory* writeFactory;
	static const WCHAR msc_fontName[];
	static const FLOAT msc_fontSize;
	float DPIScaleX = 1.0f;
	float DPIScaleY = 1.0f;
	int width;
	int height;
	
	//Variables for bitmaps
	ID2D1Bitmap* bmp;
	std::vector<ID2D1Bitmap*> Vbmp;
	int spriteWidth, spriteHeight;
	int spritesAcross;
	int BMPid;

public:

	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() {
		return renderTarget;
	}

	int CreatingBMP(wchar_t* filename);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }


	//Drawing commands

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(D2D1_RECT_F rect);
	void DrawUI(std::vector<UI>* uis);
};