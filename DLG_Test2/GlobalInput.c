#include "DGL.h"
#include "EngineControls.h"

// on pressing escape terminates the engine
void escape(void) {
	if (DGL_Input_KeyTriggered(VK_ESCAPE)) {
		stopEngine();
	}
}

// on pressing tab toggle full screen 
void tab(void) {
	if (DGL_Input_KeyTriggered(VK_TAB)) {
		FULLSCREEN = !FULLSCREEN; // toggle on/off
		handleFullScreen();
	}
}

void checkGlobalInput(void) {
	escape();
	tab();
}
