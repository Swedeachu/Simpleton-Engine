#include "DGL.h"
#include <math.h>

int rectangleToRectangleCollision(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {
	if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && height1 + y1 > y2) {
		return TRUE;
	}
	return FALSE;
}

int circleToCircleCollision(float x1, float y1, float x2, float y2, float radius1, float radius2) {
	double distance = (double) sqrt(pow((double)(x2 - x1), 2.0) + pow((double)(y2 - y1), 2.0));
	if (distance <= radius1 + radius2) {
		return TRUE;
	}
	return FALSE;
}

int circleToRectangleCollision(float circleX, float circleY, float radius, float rectangleX, float rectangleY, float rectangleWidth, float rectangleHeight) {
	float tempX = circleX;
	float tempY = circleY;
	// find closest edge for X cord
	if (circleX < rectangleX) {
		tempX = rectangleX; // left edge
	} else if (circleX > rectangleX + rectangleWidth) {
		tempX = rectangleX + rectangleWidth; // right edge
	}
	// find closest edge for Y cord
	if (circleY < rectangleY) {
		tempY = rectangleY; // top edge      
	} else if (circleY > rectangleY + rectangleHeight) {
		tempY = rectangleY + rectangleHeight; // bottom edge  
	}
	// get distance from closest edges at X and Y cords 
	float distX = circleX - tempX;
	float distY = circleY - tempY;
	float distance = (float)sqrt((distX * distX) + (distY * distY));
	// if distance is less than the radius, they are colliding
	if (distance <= radius) {
		return TRUE;
	}
	return FALSE;
}

int lineToLineCollision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	float lineA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float lineB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	if (lineA >= 0 && lineA <= 1 && lineB >= 0 && lineB <= 1) {
		return TRUE;
	}
	return FALSE;
}

int lineToRectangleHitScan(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {
	int hitLeft = lineToLineCollision(x1, y1, x2, y2, rx, ry, rx, ry + rh);
	int hitRight = lineToLineCollision(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
	int hitTop = lineToLineCollision(x1, y1, x2, y2, rx, ry, rx + rw, ry);
	int hitBottom = lineToLineCollision(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);
	if (hitLeft == TRUE || hitRight == TRUE || hitTop == TRUE || hitBottom == TRUE) {
		return TRUE;
	}
	return FALSE;
}
