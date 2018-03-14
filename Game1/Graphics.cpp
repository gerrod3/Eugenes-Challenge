#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	//I might need to initialize the Vbmp vector so i don't get errors when I start drawing sprites

	WCHAR msc_fontName[] = L"Verdana";
	FLOAT msc_fontSize = FONTSIZE::MEDIUM;  //LARGE = 40, MEDIUM = 30, SMALL = 20

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	width = rect.right;
	height = rect.bottom;

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK) return false;

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 1), &brush);
	if (res != S_OK) return false;

	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&writeFactory));

	res = writeFactory->CreateTextFormat(msc_fontName, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, msc_fontSize, L"", &textFormat);

	
	//FLOAT dpiX, dpiY;

	//factory->GetDesktopDpi(&dpiX, &dpiY);
	//DPIScaleX = dpiX / 96.0f;
	//DPIScaleY = dpiY / 96.0f;

	BMPid = -1;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

//draws from center point
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r,g,b,a));

	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}
//draws from TL point
void Graphics::DrawRectangle(D2D1_RECT_F rect) {
	
	brush->SetColor(D2D1::ColorF(BLACK_BRUSH));
	renderTarget->DrawRectangle(rect, brush, 1.0f,NULL);
}

void Graphics::DrawUI(std::vector<UI>* uis) {
	for (int i = 0; i < uis->size(); i++) {
		if (uis->at(i).visible ) //-1 bmID means that the UI is just text
		{
			if (uis->at(i).bmID != -1) {
				D2D1_RECT_F dest = { uis->at(i).HB.cord.x ,
									uis->at(i).HB.cord.y ,
									uis->at(i).HB.cord.x + uis->at(i).HB.width ,
									uis->at(i).HB.cord.y + uis->at(i).HB.height };

				D2D1_RECT_F source = { uis->at(i).spriteHB.cord.x ,
										uis->at(i).spriteHB.cord.y ,
										uis->at(i).spriteHB.cord.x + uis->at(i).spriteHB.width ,
										uis->at(i).spriteHB.cord.y + uis->at(i).spriteHB.height };

				renderTarget->DrawBitmap(
					Vbmp.at(uis->at(i).bmID), //bitmap
					dest,	//destination rectangle
					1.f,	//opacity
					D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, //interpolation mode
					source); // source rectange on bitmap
			}
			else
			{
				//set the brush, maybe add a brush/color variable to the UI struct so that I wont have to use a default for every text
				brush->SetColor(D2D1::ColorF(0.f, 0.f, 0.f));
				
				D2D1_RECT_F dest = D2D1::RectF(uis->at(i).HB.cord.x, uis->at(i).HB.cord.y, uis->at(i).HB.cord.x + uis->at(i).HB.width, uis->at(i).HB.cord.y + uis->at(i).HB.height);
				renderTarget->DrawTextW(
					uis->at(i).uiName, //the string to be printed
					wcslen(uis->at(i).uiName), //size of the string
					textFormat, //text format
					dest, // location
					brush, //brush /basically color 
					D2D1_DRAW_TEXT_OPTIONS::D2D1_DRAW_TEXT_OPTIONS_CLIP,
					DWRITE_MEASURING_MODE::DWRITE_MEASURING_MODE_NATURAL
					);
		
				//DrawRectangle(dest);
			}
			if (uis->at(i).selected) { //should draw a gray circle at 70% opacity next to the selected UI
				//this needs work, proportions are very wrong
				float pixelBuffer = 20.f;
				float smallPixelBuffer = 8.f;
				float radius = 12.5f;
				DrawCircle(uis->at(i).HB.cord.x + uis->at(i).HB.width + pixelBuffer , uis->at(i).HB.cord.y + radius + smallPixelBuffer,radius, 0.1f, 0.1f, 0.1f, 0.7f);
			}
		}

	}
}


int Graphics::CreatingBMP(wchar_t* filename) {

	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);
	//TODO ERROR CHECKING

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);


	renderTarget->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	//spriteWidth = bmp->GetSize().width;
	//spriteHeight = bmp->GetSize().height;
	//spritesAcross = 1;
	//bmpFilenames.push_back(filename);
	BMPid++;
	Vbmp.push_back(bmp);

	return BMPid;
}