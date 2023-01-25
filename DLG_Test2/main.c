#include "Resource.h"
#include "DGL.h"
#include "meshBuilder.h"
#include "game.h"
#include "EngineControls.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int result;
	if (DGL_System_HandleWindowsMessage(message, wParam, lParam, &result)) {
		return result;
	}

	switch (message) {
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
	// init the window with all its properties
	DGL_SysInitInfo initInfo;
	initInfo.mAppInstance = hInstance;
	initInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	initInfo.mMaxFrameRate = 60;
	initInfo.mShow = nCmdShow;
	initInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;
	initInfo.mWindowTitle = "Core Mechanic Prototype";
	initInfo.mWindowHeight = 1080;
	initInfo.mWindowWidth = 1920;
	initInfo.mCreateConsole = TRUE;
	initInfo.pWindowsCallback = WndProc;
	initInfo.mWindowIcon = IDI_DLGTEST2;
	HWND windowHandle = DGL_System_Init(&initInfo);
	if (windowHandle == NULL) {
		return 1;
	}

	// set fullscreen mode to true and toggle it on
	FULLSCREEN = TRUE;
	handleFullScreen();
	
	// get the engine started
	startEngine();

	// the first thing we do after initing the window and starting the engine is setting our game state and we can go from there
	setGameState(&gameInit, &gameLoop, &gameExit);

	return 0;
}
