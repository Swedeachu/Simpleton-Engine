#include <stdio.h>
#include <stdlib.h>
#include "DGL.h"
#include "meshBuilder.h"
#include "gameObject.h"
#include "Collision.h"

int ID = 0; // this variable is used for keeping track of game objects, every game object has a unique ID correlating to creation order, the first game object has an ID of 1

GameObject* head = NULL;

// creating a game object also returns it
GameObject* createGameObject(float x, float y, float width, float height) {
	ID++; // increment ID as a new game object is made
	GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject)); // create the object
	if (gameObject) {
		// assign properties accordingly
		gameObject->ID = ID;
		gameObject->x = x;
		gameObject->y = y;
		gameObject->previousX = x;
		gameObject->previousY = y;
		gameObject->width = width;
		gameObject->height = height;
		gameObject->collideable = TRUE;

		// default directions are right and up
		gameObject->xDirection = RIGHT;
		gameObject->yDirection = UP;

		// default collider type is rectangle
		gameObject->collider = RECTANGLE;

		// by default it is just a white color filled mesh without an assigned texture
		gameObject->renderType = COLOR_FILL;
		gameObject->texture = NULL;
		gameObject->mesh = buildRectangleMesh((DGL_Color) { 0.0f, 0.0f, 0.0f, 1.0f });

		gameObject->next = head;
		head = gameObject;

		return gameObject;
	}
	return NULL;
}

// delete a specific game object, can be done like so: deleteGameObjectByID(gameObject->id);
void deleteGameObjectByID(int id) {
	GameObject* current = head;
	GameObject* previous = NULL;
	while (current != NULL) {
		if (current->ID == id) {
			DGL_Graphics_FreeMesh(&current->mesh);
			// DGL_Graphics_FreeTexture(&current->texture);
			if (previous == NULL) {
				head = current->next;
			} else {
				previous->next = current->next;
			}
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

// clear all objects in memory
void freeAllGameObjects(void) {
	GameObject* current = head;
	while (current != NULL) {
		GameObject* next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

// get the amount of game objects present
int getGameObjectCount(void) {
	int count = 0;
	GameObject* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

// check if a game object is colliding with another game object
int gameObjectsColliding(GameObject* object1, GameObject* object2) {
	if (object1->collideable == TRUE && object2->collideable == TRUE) {
		enum COLLIDER colliderType1 = object1->collider;
		enum COLLIDER colliderType2 = object2->collider;
		float x1 = object1->x;
		float y1 = object1->y;
		float width1 = object1->width;
		float height1 = object1->height;
		float x2 = object2->x;
		float y2 = object2->y;
		float width2 = object2->width;
		float height2 = object2->height;
		float radius1 = width1 / 2;
		float radius2 = width2 / 2;
		if (colliderType1 == RECTANGLE && colliderType2 == RECTANGLE) {
			return rectangleToRectangleCollision(x1, y1, width1, height1, x2, y2, width2, height2);
		} else if (colliderType1 == CIRCLE && colliderType2 == CIRCLE) {
			return circleToCircleCollision(x1, y1, x2, y2, radius1, radius2);
		} else if ((colliderType1 == CIRCLE && colliderType2 == RECTANGLE) || (colliderType1 == RECTANGLE && colliderType2 == CIRCLE)) {
			// for my math to work just have to do a slight translation up and to the left for circle to rectangle collision
			if (colliderType1 == CIRCLE) {
				float translatedX = x2 - (width1 / 2);
				float translatedY = y2 - (height2 / 2);
				return circleToRectangleCollision(x1, y1, radius1, translatedX, translatedY, width2, height2);
			} else {
				float translatedX = x1 - (width2 / 2);
				float translatedY = y1 - (height1 / 2);
				return circleToRectangleCollision(x2, y2, radius2, translatedX, translatedY, width1, height1);
			}
		}
	}
	return FALSE;
}

// loops through all game objects and checks if any are colliding with the specified game object
void handleCollide(GameObject* object) {
	GameObject* current = head;
	while (current != NULL) {
		GameObject* next = current->next;
		if (current->ID != object->ID) { // can not not collide with self
			if (object->collideable == TRUE) {
				if (gameObjectsColliding(object, current) == TRUE) {
					// if collided, move both objects back to position they were last at before colliding
					object->x = object->previousX;
					object->y = object->previousY;
					current->x = current->previousX;
					current->y = current->previousY;
				} else {
					object->previousX = object->x;
					object->previousY = object->y;
				}
			}
		}
		current = next;
	}
}

// gets a texture and puts it on a mesh and draws it with a certain width and height, all from the specifed gameObjects values
void renderGameObject(GameObject* gameObject) {
	// get properties
	int renderType = gameObject->renderType;
	// need to translate x over to render top left mode
	float translatedCornerX = gameObject->x + (gameObject->width / 2);
	DGL_Vec2 position = { translatedCornerX, gameObject->y };
	DGL_Vec2 scale = { gameObject->width, gameObject->height };
	DGL_Graphics_SetCB_TransformData(&position, &scale, 0.0f);
	// render typing
	if (renderType == TEXTURE) {
		if (gameObject->texture != NULL && gameObject->texture != 0) {
			DGL_Graphics_SetShaderMode(DGL_SM_TEXTURE);
			DGL_Graphics_SetTexture(gameObject->texture);
		}
		DGL_Graphics_DrawMesh(gameObject->mesh, DGL_DM_TRIANGLESTRIP);
	} else if (renderType == WRAPPED_TEXTURE) {
		// TO DO : implement
	} else if (renderType == COLOR_FILL) {
		DGL_Graphics_SetShaderMode(DGL_SM_COLOR);
		DGL_Graphics_DrawMesh(gameObject->mesh, DGL_DM_TRIANGLESTRIP);
	}
}

// iterate through all game objects and execute an array of callbacks on each of them
// requires to specify the amount of callbacks in the array for the second parameter
void iterateAndExecuteCallbacksOnGameObjects(void (*callbacks[])(GameObject*), int numCallBacks) {
	GameObject* current = head;
	while (current != NULL) {
		GameObject* next = current->next;
		for (int i = 0; i < numCallBacks; i++) {
			callbacks[i](current);
		}
		current = next;
	}
}

// executes all the basic functions on a game object (collision, rendering, physics)
void handleAllGameObjects(void) {
	CallBacks callbacks[] = { handleCollide, renderGameObject };
	iterateAndExecuteCallbacksOnGameObjects(callbacks, 2);
}

// iterates through all game objects and executes a single callback function
void iterateGameObjectsWithCallback(void (*callback)(GameObject*)) {
	GameObject* current = head;
	while (current != NULL) {
		GameObject* next = current->next;
		callback(current);
		current = next;
	}
}

// draws all objects on screen
void renderAllGameObjects(void) {
	iterateGameObjectsWithCallback(renderGameObject);
}

// iterates through each game object which then has each game object iterate through all the other game objects to check if its colliding with any
void handleAllGameObjectCollision(void) {
	iterateGameObjectsWithCallback(handleCollide);
}
