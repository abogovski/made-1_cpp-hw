#pragma once

#include "car.h"
#include <stdbool.h>
#include <stdio.h>

extern size_t DEFAULT_BUF_SIZE;

bool readCar(FILE* file, Car* car);
void printCar(FILE* file, const Car* car);
