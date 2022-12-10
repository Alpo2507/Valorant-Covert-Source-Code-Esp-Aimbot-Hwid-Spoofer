#define opacity(v)				(255 * v) / 100
#define RedColor(a)				D3DCOLOR_ARGB(opacity(a), 255, 0, 0)
#define GreenColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 255, 0)
#define BlueColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 0, 255)
#define YellowColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 255, 0)
#define OrangeColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 125, 0)
#define WhiteColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 255, 255)
#define BlackColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 0, 0)

#include "hD3D9.h"

IDirect3D9Ex* dx_Object = NULL;
IDirect3D9Ex* d3d;
HWND Game1Wnd = NULL;

IDirect3DDevice9Ex* dx_Device = NULL;
D3DPRESENT_PARAMETERS dx_Params;
ID3DXLine* dx_Line;
ID3DXFont* dx_Font = 0;

int Width1 = GetSystemMetrics(SM_CXSCREEN);
int Height1 = GetSystemMetrics(SM_CYSCREEN);
float ScreenCenterX1 = Width1/2;
float ScreenCenterY1 = Height1/2;

/*
We require to initialize the D3D drawing, so we require hWnd. Windows identifies each form or application by assigning it a handle or also known as hWnd.
*/
bool D3D9Init(HWND hWnd)
{
    if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d)))
        exit(3);
    // d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.hDeviceWindow = hWnd;
    d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferWidth = 0;
    d3dpp.BackBufferHeight = 0;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    d3dpp.Windowed = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if (FAILED(d3d->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, 0, &draw.device)))
    {
        d3d->Release();
        exit(4);
    }
    // d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &draw.device);

     //D3DXCreateLine(draw.device, &xwwwwwwqq);

    d3d->Release();//boşalt


    return true;
}

void CleanupD3D()
{
    if (draw.GetDevice() != NULL)
    {
        draw.GetDevice()->EndScene();
        draw.GetDevice()->Release();
    }
    if (d3d != NULL)
    {
        d3d->Release();
    }
}

