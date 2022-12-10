#define _CRT_SECURE_NO_WARNINGS
#include "hDraw.h"
#include <time.h>
#include <string>

#define M_PI                       3.14159265358979323846f

Draw draw;

INT Fps = 0;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;



void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
{
	D3DXVECTOR2 Line[128];
	float Step = M_PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < M_PI * 2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	dx_Line->Begin();
	dx_Line->Draw(Line, Count, Color);
	dx_Line->End();
}

void Draw::FPSCheck(std::string& str)
{
	CurrentTickCount = clock() * 0.001f;
	Fps++;

	if ((CurrentTickCount - LastTickCount) > 1.0f)
	{
		LastTickCount = CurrentTickCount;
		str = std::to_string(Fps);
		Fps = 0;
	}
}

int Draw::TextWidth(string Text)
{
	RECT rect = { 0, 0, 0, 0 };
	draw.font->DrawText(NULL, Text.c_str(), -1, &rect, DT_CALCRECT, NULL);
	return rect.right - rect.left;
}


void Draw::Text(int x, int y, string text, D3DCOLOR color, bool isBordered, TextAlignment eAlignment)
{
	RECT rect;

	/*if (isBordered)
	{
		struct ShadowStruct { int x; int y; };
		ShadowStruct shadowOffset[] = { {-1, 0}, {+1, 0}, {0, -1}, {0, +1} };

		for (int i = 0; i < GetSizeOf(shadowOffset); i++)
		{
			SetRect(&rect, x + shadowOffset[i].x, y + shadowOffset[i].y, x + shadowOffset[i].x, y + shadowOffset[i].y);
			this->font->DrawTextA(NULL, text.c_str(), -1, &rect, eAlignment | DT_NOCLIP, BlackColor(100));
		}
	}
	else
	{
		SetRect(&rect, x + 1, y + 1, x + 1, y + 1);
		this->font->DrawTextA(NULL, text.c_str(), -1, &rect, eAlignment | DT_NOCLIP, BlackColor(50));
	}
	*/
	SetRect(&rect, x, y, x, y);
	this->font->DrawTextA(NULL, text.c_str(), -1, &rect, eAlignment | DT_NOCLIP, color);
}

void Draw::Texture(int x, int y, LPDIRECT3DTEXTURE9 dTexture, LPD3DXSPRITE sprite)
{
	// Allow use of alpha values
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, 0.0f);
	sprite->Draw(dTexture, NULL, NULL, &pos, 0xFFFFFFFF);

	sprite->End();
}

/*
	Draws a textures specified by textureItems
*/
void Draw::Image(int x, int y, TextureItems* textureItems)
{

	Draw::Texture(x, y, textureItems->imagetex, textureItems->sprite);
}

void Draw::Line(float x, float y, float x2, float y2, D3DCOLOR color)
{
	Vertex v[2] =
	{
		{x,		y,	0.0f, 1.0f, color},
		{x2,	y2,	0.0f, 1.0f, color},
	};
	this->device->DrawPrimitiveUP(D3DPT_LINELIST, 1, v, sizeof(Vertex));
}

void Draw::Border(float x, float y, float w, float h, D3DCOLOR color)
{
	Vertex vertices[6] =
	{
		x + w, y,		0.0f, 1.0f, color, 0.0f, 0.0f,
		x + w, y + h,	0.0f, 1.0f, color, 0.0f, 0.0f,
		x, y + h,		0.0f, 1.0f, color, 0.0f, 0.0f,

		x, y + h,		0.0f, 1.0f, color, 0.0f, 0.0f,
		x, y,			0.0f, 1.0f, color, 0.0f, 0.0f,
		x + w, y,		0.0f, 1.0f, color, 0.0f, 0.0f,
	};

	this->device->DrawPrimitiveUP(D3DPT_LINESTRIP, 5, vertices, sizeof(Vertex));
}

void Draw::Rectangle(float x, float y, float w, float h, D3DCOLOR startColor, D3DCOLOR endColor, D3DCOLOR borderColor)
{
	if (endColor == NULL)
		endColor = startColor;

	Vertex vertices[4] =
	{
		x,  y,			0.0f, 1.0f, startColor, 0.0f, 0.0f,
		x + w, y,		0.0f, 1.0f, startColor, 1.0f, 0.0f,

		x + w, y + h,	0.0f, 1.0f, endColor, 1.0f, 1.0f,
		x,  y + h,		0.0f, 1.0f, endColor, 0.0f, 1.0f,
	};

	this->device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(Vertex));

	if (borderColor != NULL)
		Border(x - 1, y - 1, w + 1, h + 1, borderColor);
}

void Draw::Box(float x, float y, float distance_modifier, D3DCOLOR color) {
	int head_x = x;
	int head_y = y;
	int start_x = head_x - 35 / distance_modifier;
	int start_y = head_y - 15 / distance_modifier;
	int end_x = head_x + 35 / distance_modifier;
	int end_y = head_y + 155 / distance_modifier;
	//dx_Line->SetWidth(2);
	//dx_Line->Draw(points, 5, D3DCOLOR_RGBA(r, g, b, a));
}

int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT ShadowPos;
	ShadowPos.left = x + 1;
	ShadowPos.top = y + 1;
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	ifont->DrawTextA(0, String, strlen(String), &ShadowPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r / 3, g / 3, b / 3));
	ifont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
}
int DrawShadowString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT Font;
	Font.left = x;
	Font.top = y;
	RECT Fonts;
	Fonts.left = x + 1;
	Fonts.top = y;
	RECT Fonts1;
	Fonts1.left = x - 1;
	Fonts1.top = y;
	RECT Fonts2;
	Fonts2.left = x;
	Fonts2.top = y + 1;
	RECT Fonts3;
	Fonts3.left = x;
	Fonts3.top = y - 1;
	ifont->DrawTextA(0, String, strlen(String), &Fonts3, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts2, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts1, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
}

void GradientFunc(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int iColorr, iColorg, iColorb;
	for (int i = 1; i < h; i++)
	{
		iColorr = (int)((float)i / h * r);
		iColorg = (int)((float)i / h * g);
		iColorb = (int)((float)i / h * b);
		//DrawFilled(x, y + i, w, 1, r - iColorr, g - iColorg, b - iColorb, a);
	}
}
void DrawLine(float x, float y, float xx, float yy, int r, int g, int b, int a)
{

	dx_Line[0].SetWidth(1);
	dx_Line[0].SetGLLines(0);
	dx_Line[0].SetAntialias(1);
	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = x;
	v2Line[0].y = y;
	v2Line[1].x = xx;
	v2Line[1].y = yy;
	dx_Line[0].Begin();
	dx_Line[0].Draw(v2Line, 2, D3DCOLOR_ARGB(a, r, g, b));
	dx_Line[0].End();

	//D3DXVECTOR2 dLine[2];

	//dx_Line->SetWidth(1);

	//dLine[0].x = x;
	//dLine[0].y = y;

	//dLine[1].x = xx;
	//dLine[1].y = yy;

	//dx_Line->Draw(dLine, 2, D3DCOLOR_ARGB(a, r, g, b));

}
void DrawFilled(float x, float y, float w, float h, D3DCOLOR color)
{
	D3DXVECTOR2 vLine[2];

	dx_Line->SetWidth(w);

	vLine[0].x = x + w / 2;
	vLine[0].y = y;
	vLine[1].x = x + w / 2;
	vLine[1].y = y + h;

	dx_Line->Begin();
	dx_Line->Draw(vLine, 2, color);
	dx_Line->End();
}
void DrawBox(float x, float y, float width, float height, D3DCOLOR color)
{
	D3DXVECTOR2 points[5];
	points[0] = D3DXVECTOR2(x, y);
	points[1] = D3DXVECTOR2(x + width, y);
	points[2] = D3DXVECTOR2(x + width, y + height);
	points[3] = D3DXVECTOR2(x, y + height);
	points[4] = D3DXVECTOR2(x, y);
	//dx_Line->SetWidth(px);
	dx_Line->Draw(points, 5, color);
}
void DrawBOX(float x, float y, float xx, float yy, float width, D3DCOLOR color) {
	D3DXVECTOR2 points[5];
	points[0] = D3DXVECTOR2(x - (width / 2), y);
	points[1] = D3DXVECTOR2(x + (width / 2), y);
	points[2] = D3DXVECTOR2(xx + (width / 2), yy);
	points[3] = D3DXVECTOR2(xx - (width / 2), yy);
	points[4] = D3DXVECTOR2(x - (width / 2), y);
	dx_Line->SetWidth(2);
	dx_Line->Draw(points, 5, color);
}
void DrawGUIBox(float x, float y, float w, float h, int r, int g, int b, int a, int rr, int gg, int bb, int aa)
{
	DrawBox(x, y, w, h, D3DCOLOR_ARGB(255, r, g, b));
	DrawFilled(x, y, w, h, D3DCOLOR_ARGB(255, rr, gg, bb));
}
void DrawHealthBar(float x, float y, float w, float h, int r, int g, int b, int a)
{
	DrawFilled(x, y, w, h, D3DCOLOR_ARGB(a, r, g, b));
}
void DrawHealthBarBack(float x, float y, float w, float h, int a)
{
	DrawFilled(x, y, w, h, D3DCOLOR_ARGB(255, 0, 0, 0));
}
//void DrawCenterLine(float x, float y, int width, int r, int g, int b)
//{
//	D3DXVECTOR2 dPoints[2];
//	dPoints[0] = D3DXVECTOR2(x, y);
//	dPoints[1] = D3DXVECTOR2(Width / 2, Height);
//	dx_Line->SetWidth(width);
//	dx_Line->Draw(dPoints, 2, D3DCOLOR_RGBA(r, g, b, 255));
//}
