#include "pch.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")

// global declarations
LPDIRECT3D9 d3d;	// the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev; // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = nullptr; // the pointer to the vertex buffer

// function prototypes
void initD3D(HWND hWnd);	// sets up and initialized Direct3D
void render_frame(void);	// renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory
void init_graphics(void);	// 3D declarations

struct CUSTOMVERTEX { FLOAT x, y, z, rhw; DWORD color; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand)
{
	UNREFERENCED_PARAMETER(previousInstance);
	UNREFERENCED_PARAMETER(commandLine);

	// Code for testing instance of SList only
	SList<int> list{};
	list.pushFront(1);
	auto val = *list.begin();
	val = 2;
//	++iterRef;
//	++iter;

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
	initD3D(hWnd);
	// this struct holds Windows event messages
	MSG msg;

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
		render_frame();
	}

	cleanD3D();
	// return this part of the WM_QUIT message to Windows
	return static_cast<int>(msg.wParam);
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
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	// create a device class using this information and infromation from the d3dpp struct
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	init_graphics(); // call the function to initialize the triangle
}

/**
 * This is the function used to render a single frame
 */
void render_frame(void)
{
	// clear the window to a deep blue
	d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	d3ddev->BeginScene();	// begins the 3D scene	

	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);
	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	// copy the vertex buffer to the back buffer
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	// do 3D rendering on the back buffer here
	d3ddev->EndScene();		// ends the 3D scene
	d3ddev->Present(nullptr, nullptr, nullptr, nullptr); // displays the created frame
}

/**
 * This is the function that clenas up Direct3D and COM
 */
void cleanD3D(void)
{
	v_buffer->Release(); // close and release the vertex buffer
	d3ddev->Release(); // close and release the 3D device
	d3d->Release();	   // close and release Direct3D
}

/**
 * This is the function that puts the 3D models into the video RAM
 */
void init_graphics(void)
{
	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] =
	{
		{ 400.0f, 62.5f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255) },
		{650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0)},
		{150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)}
	};

	// crate a vertex buffer interface called v_buffer
	d3ddev->CreateVertexBuffer(
		3*sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		nullptr
	);

	void* pVoid; // a void pointer

	// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
}