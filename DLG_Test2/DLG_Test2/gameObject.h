#pragma once
#include "DGL.h"

#define RIGHT 1
#define LEFT -1
#define UP 1
#define DOWN -1

enum SPRITE_RENDER_TYPE {
	TEXTURE, // a single texture is rendered and stretched to fit if needed for the mesh
	WRAPPED_TEXTURE, // a repeating texture is rendered across the mesh when possible
	COLOR_FILL // the mesh is just a rendered shape with a fill color and no texture
};

enum COLLIDER {
	CIRCLE,
	RECTANGLE
};

typedef struct GameObject {
	int ID;
	float x;
	float y;
	float width;
	float height;
	int xDirection;
	int yDirection;
	int collideable;
	enum SPRITE_RENDER_TYPE renderType;
	enum COLLIDER collider;
	DGL_Color color;
	DGL_Texture* texture;
	DGL_Mesh* mesh;
	float previousX;
	float previousY;
	struct GameObject* next;
} GameObject;

typedef void(*CallBacks)(GameObject*);

GameObject* createGameObject(float x, float y, float width, float height); // creates a basic game object with a lot of default values to be manually changed
void deleteGameObjectByID(int id); // delete a specific game object by id
void freeAllGameObjects(void); // deletes all game objects from memory
int getGameObjectCount(void); // get the amount of alive game objects 
void renderGameObject(GameObject* gameObject); // draw a specifc game object
void handleAllGameObjects(void); // handle collision, physics, behavior, rendering, all in one function
void renderAllGameObjects(void); // draw all objects on screen with there current properties
