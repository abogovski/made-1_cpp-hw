#pragma once

#include "body.h"

#define MAX_MODEL_STR_LEN 15

typedef struct Car {
    double enginePower;
    double maxSpeed;
    double fuelConsumption;
    Body body;
    char model[MAX_MODEL_STR_LEN + 1];
} Car;

extern const Car UNDEFINED_CAR;

double carDistance(const Car* left, const Car* right);
