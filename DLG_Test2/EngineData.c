#include "DGL.h"

int getFPS(void) {
	int FPS = 0;
	double deltaFrameTime = DGL_System_GetDeltaTime();
	if (deltaFrameTime > 0) {
		FPS = (int)(1.0f / (float)deltaFrameTime) + 1;
	}
	return FPS;
}
