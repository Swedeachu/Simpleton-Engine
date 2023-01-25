#pragma once

int rectangleToRectangleCollision(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
int circleToCircleCollision(float x1, float y1, float x2, float y2, float radius1, float radius2);
int circleToRectangleCollision(float circleX, float circleY, float radius, float rectangleX, float rectangleY, float rectangleWidth, float rectangleHeight);
int lineToLineCollision(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
int lineToRectangleHitScan(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh);
