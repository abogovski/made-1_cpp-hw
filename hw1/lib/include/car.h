#pragma once

#include "body.h"

#define MAX_MODEL_STR_LEN 15

struct Car {
    double enginePower;
    double maxSpeed;
    double fuelConsumption;
    enum Body body;
    char* model;
};

void swapCars(struct Car* left, struct Car* right);
double carDistance(const struct Car* left, const struct Car* right);
