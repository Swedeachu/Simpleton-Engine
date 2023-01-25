#include "DGL.h"
#include "MathUtil2D.h"
#include <math.h>

// this function creates a 1x1 mesh object that we can scale up and assign textures to
DGL_Mesh* buildRectangleMesh(DGL_Color color) {
	float width = 1.0f;
	float height = 1.0f;
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	// Tell DGL that we are starting a new mesh
	DGL_Graphics_StartMesh();
	// First triangle:
	// Add a vertex at the bottom-left corner
	DGL_Vec2 pos = { -halfWidth, -halfHeight };
	DGL_Vec2 uv = { 0.0f, 1.0f };
	DGL_Graphics_AddVertex(&pos, &color, &uv);
	// Add a vertex at the top-left corner
	pos = (DGL_Vec2){ -halfWidth, halfHeight };
	uv = (DGL_Vec2){ 0.0f, 0.0f };
	DGL_Graphics_AddVertex(&pos, &color, &uv);
	// Add a vertex at the top-right corner
	pos = (DGL_Vec2){ halfWidth, halfHeight };
	uv = (DGL_Vec2){ 1.0f, 0.0f };
	DGL_Graphics_AddVertex(&pos, &color, &uv);
	// Second triangle:
	// Add a vertex at the bottom-left corner
	pos = (DGL_Vec2){ -halfWidth, -halfHeight };
	uv = (DGL_Vec2){ 0.0f, 1.0f };
	DGL_Graphics_AddVertex(&pos, &color, &uv);
	// Add a vertex at the top-right corner
	pos = (DGL_Vec2){ halfWidth, halfHeight };
	uv = (DGL_Vec2){ 1.0f, 0.0f };
	DGL_Graphics_AddVertex(&pos, &color, &uv);
	// Add a vertex at the bottom-right corner
	pos = (DGL_Vec2){ halfWidth, -halfHeight };
	uv = (DGL_Vec2){ 1.0f, 1.0f };
	DGL_Graphics_AddVertex(&pos, &color, &uv);
	// Done adding vertices, so save the mesh object
	DGL_Mesh* mesh = DGL_Graphics_EndMesh();
	return mesh;
}

DGL_Mesh* buildCircleMesh(DGL_Color color) {
	// TO DO : implement
	return buildRectangleMesh(color);
}
