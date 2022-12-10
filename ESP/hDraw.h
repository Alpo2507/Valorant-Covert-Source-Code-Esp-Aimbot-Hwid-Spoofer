#ifndef HDRAWFUNC_H
#define HDRAWFUNC_H

#include "hD3D9.h"

#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )

#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



using namespace std;

enum TextAlignment { kLeft, kCenter, kRight };

struct TextureItems
{
	LPDIRECT3DTEXTURE9 imagetex = nullptr; //textute our image will be loaded into
	LPD3DXSPRITE sprite = nullptr; //sprite to display our image
};


class Draw
{
public:
	Draw()
	{
		isInitialized = false;
	}

	TextureItems myTexture;
	IDirect3DDevice9Ex* device;
	LPD3DXFONT font;
	void Init() { this->isInitialized = true; }
	bool IsInitialized() { return this->isInitialized; }

	void Texture(int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE sprite);
	void Image(int x, int y, TextureItems* textureItems);
	int TextWidth(string text);
	void Text(int x, int y, string text, D3DCOLOR color, bool isBordered = false, TextAlignment eAlignment = TextAlignment::kLeft);
	void Line(float x, float y, float x2, float y2, D3DCOLOR color);
	void Border(float x, float y, float w, float h, D3DCOLOR color);
	void Rectangle(float x, float y, float w, float h, D3DCOLOR startColor, D3DCOLOR endColor = NULL, D3DCOLOR borderColor = NULL);
	void Box(float x, float y, float distance_modifier, D3DCOLOR color);
	void FPSCheck(std::string& str);
	IDirect3DDevice9Ex* GetDevice() { return this->device; }
private:
	struct Vertex
	{
		float x, y, z, h;
		D3DCOLOR color;
		float tu, tv;
		static DWORD FVF;
	};

	bool isInitialized;

};

#define opacity(v)				(255 * v) / 100
//
//#define RedColor(a)				D3DCOLOR_ARGB(opacity(a), 255, 0, 0)
//#define GreenColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 255, 0)
//#define BlueColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 0, 255)
//#define YellowColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 255, 0)
//#define OrangeColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 125, 0)
//#define WhiteColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 255, 255)
//#define BlackColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 0, 0)

extern Draw draw;

void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color);

void GradientFunc(int x, int y, int w, int h, int r, int g, int b, int a);
void DrawCenterLine(float x, float y, int r, int g, int b, int a);
void DrawLine(float x, float y, float xx, float yy, int r, int g, int b, int a);
void DrawFilled(float x, float y, float w, float h, D3DCOLOR color);
void DrawBox(float x, float y, float width, float height, D3DCOLOR color);
void DrawBOX(float x, float y, float xx, float yy, float width, D3DCOLOR color);
void DrawGUIBox(float x, float y, float w, float h, int r, int g, int b, int a, int rr, int gg, int bb, int aa);
void DrawHealthBar(float x, float y, float w, float h, int r, int g, int b, int a);
void DrawHealthBarBack(float x, float y, float w, float h, int a);

int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont);
int DrawShadowString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont);



#endif


