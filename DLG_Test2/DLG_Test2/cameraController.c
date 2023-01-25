#include "DGL.h"

// controlled by scroll wheel to zoom in and out
void controlCameraZoom(void) {
	int delta = DGL_Input_GetMouseScrollDelta();
	if (delta != 0) {
		float cameraZoom = DGL_Camera_GetZoom();
		cameraZoom -= delta / 2.0f;
		if (cameraZoom >= 1.0f) {
			DGL_Camera_SetZoom(cameraZoom);
		}
	}
}