#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include "SList.h"

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")

// global declarations
LPDIRECT3D9 d3d;			// the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;	// the pointer to the device class

// function prototypes
void initD3D(HWND hWnd);	// sets up and initialized Direct3D
void render_frame(void);	// renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",		// name of the window class
		L"Simple DirectX Game", // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		560,					// x-position of the window
		240,					// y-position of the window
		800,					// width of the window
		600,					// height of the window
		nullptr,				// we have no parent window, NULL
		nullptr,				// we aren't using menus, NULL
		hInstance,				// application handle
		nullptr);				// used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, showCommand);

	// this struct holds Windows event messages
	MSG msg;

	initD3D(hWnd);

	while (true)
	{
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);
		}

		// If the message is WM_QUOT, exit the while loop
		if (msg.message == WM_QUIT)
			break;

		// Run game code here
		// ...
		// ...
		render_frame();
	}

	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);

	cleanD3D();

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

/**
 * this is the main message handler for the program
 */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} break;
		default: 
			break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}


/**
 * this function initializes and prepares Direct3D for use
 */
void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);	// create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;			// create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));		// clear out the struct for use
	d3dpp.Windowed = true;					// program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Discard old frames
	d3dpp.hDeviceWindow = hWnd;				// set the window to be used by Direct3D

	// create a device class using this information and infromation from the d3dpp struct
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);
}

/**
 * This is the function used to render a single frame
 */
void render_frame(void)
{
	// clear the window to a deep blue
	d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	d3ddev->BeginScene();	// begins the 3D scene

	// do 3D rendering on the back buffer here
	d3ddev->EndScene();		// ends the 3D scene
	d3ddev->Present(nullptr, nullptr, nullptr, nullptr); // displays the created frame
}

/**
 * This is the function that clenas up Direct3D and COM
 */
void cleanD3D(void)
{
	d3ddev->Release(); // close and release the 3D device
	d3d->Release();	   // close and release Direct3D
}