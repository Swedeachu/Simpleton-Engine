#include <stdlib.h>

int randomRangeInt(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

double randomRangeDouble(double min, double max) {
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

float randomRangeFloat(float min, float max) {
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}
