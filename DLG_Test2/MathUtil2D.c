#include <math.h>

double distance2D(float x1, float y1, float x2, float y2) {
	return (double)sqrt(pow((double)(x2 - x1), 2.0) + pow((double)(y2 - y1), 2.0));
}
