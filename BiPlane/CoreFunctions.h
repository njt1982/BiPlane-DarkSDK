#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randFloat(void) {
	return (float)rand() / (float)RAND_MAX;
}
