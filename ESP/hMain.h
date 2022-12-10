#ifndef HMAIN_H
#define HMAIN_H


#include <iostream>
#include <Windows.h>

#include "hD3D9.h"

#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

extern MSG Message; // Queue Nachricht

void Render();

#endif