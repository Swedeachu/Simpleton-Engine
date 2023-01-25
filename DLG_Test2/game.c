#include "DGL.h"
#include "stdio.h"
#include <stdlib.h>
#include "gameObject.h"
#include "meshBuilder.h"
#include "EngineControls.h"
#include "cameraController.h"

GameObject* ball; // used in main loop
GameObject* player; // used everywhere

void gameInit(void) {
	// clean up from any previous game states
	freeAllGameObjects();
	// some basic graphics and background inits
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTextureSamplerData(DGL_SM_TEXTURE, DGL_AM_MIRROR);
	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 1.0f, 1.0f, 1.0f, 1.0f });
	DGL_Camera_SetZoom(1.0f);

	// texture to be used later on
	DGL_Texture* ballTexture = DGL_Graphics_LoadTexture("./Assets/ball.png");

	// create player object
	player = createGameObject(960, 540, 64, 64);
	player->mesh = buildCircleMesh((DGL_Color) { 1.0f, 0.0f, 0.0f, 1.0f });
	player->texture = ballTexture;
	player->collider = CIRCLE;
	player->renderType = TEXTURE;

	// create game objects

	GameObject* floor = createGameObject(0, 64, 1280, 64);
	ball = createGameObject(500, 500, 64, 64);

	// add texture to a game object
	ball->texture = ballTexture;
	ball->collider = CIRCLE;
	ball->renderType = TEXTURE; // remember to do this! (default render type is color fill so need to change it)

	// set camera position to look at center of screen
	DGL_Vec2 cameraPosition = { 960, 540 };
	DGL_Camera_SetPosition(&cameraPosition);
}

void gameExit(void) {
	// DGL_System_Exit(); // actually dont need to do this 
}

// just quick function to make a game object travel up and down in place 
void bounceGameObject(GameObject* gameObject) {
	float y = gameObject->y;
	if (y <= 400 || y >= 900) {
		gameObject->yDirection *= -1;
	}
	y += 5 * gameObject->yDirection;
	gameObject->y = y;
}

void gameLoop(void) {
	bounceGameObject(ball);

	// mouse scrolling with camera zoom
	controlCameraZoom();

	// player movement
	if (DGL_Input_KeyDown('W')) {
		player->y += 10;
	}
	if (DGL_Input_KeyDown('A')) {
		player->x -= 10;
	}
	if (DGL_Input_KeyDown('S')) {
		player->y -= 10;
	}
	if (DGL_Input_KeyDown('D')) {
		player->x += 10;
	}

	DGL_Camera_SetPosition(&(DGL_Vec2) { player->previousX, player->previousY }); // move camera position last

	// restarts game state with R key being pressed
	if (DGL_Input_KeyDown('R')) {
		setGameState(&gameInit, &gameLoop, &gameExit);
	}

	handleAllGameObjects(); // handle collision, physics, behavior, rendering

}
