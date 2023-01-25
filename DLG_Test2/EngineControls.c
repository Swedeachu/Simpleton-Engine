#include "DGL.h"
#include "EngineControls.h"
#include "GlobalInput.h"

// start the engine
void startEngine(void) {
	RUNNING = TRUE;
}

// will cause our game state loop to stop
void stopEngine(void) {
	RUNNING = FALSE;
}

// make DGL handle and update in frames 
void startFrame(void) {
	DGL_System_FrameControl();
	DGL_System_Update();
	DGL_Graphics_StartDrawing();
}

// make DGL finish drawing meshes and stuff and also handle if the user closed the window, which would stop the engine
void completeFrame(void) {
	DGL_Graphics_FinishDrawing();
	if (!DGL_System_DoesWindowExist()) { // if user closed the window end the game and close window
		stopEngine();
		DGL_System_Exit();
	}
}

// arguments for an init function, loop function, and close function 
void setGameState(void (*initFunction)(), void (*loopFunction)(), void (*closeFunction)()) {
	(*initFunction)(); // Run the init function first once
	while (RUNNING == TRUE) { // loop does not stop until you make the engine stop with stopEngine(), which will then cause the close function to execute
		startFrame(); // control, update, and start drawing
		checkGlobalInput(); // global hot keys that will always impact the engine (escape, toggle full screen, etc)
		(*loopFunction)(); // Run the loop function
		completeFrame(); // finish drawing and check is user closed window
	}
	(*closeFunction)(); // Run the close function at the end, probably best used for resource clean up and log file saving etc
}

// based on the engine variable FULLSCREEN the window will be handled to go in or out of full screen mode
void handleFullScreen(void) {
	if (FULLSCREEN == TRUE) {
		DGL_Window_SetStyle(WS_EX_TOPMOST); // goes into full screen
	} else {
		DGL_Window_SetStyle(WS_OVERLAPPEDWINDOW); // windowed mode
	}
}
