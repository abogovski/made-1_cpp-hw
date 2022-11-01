#include "car.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define PENALTY 1

const Car UNDEFINED_CAR = {0, 0, 0, Undefined, ""};

static double scalarDist(double left, double right)
{
    if (isnan(left) || isnan(right)) {
        return 0.0;
    }
    return fabs(left - right);
}

static double bodyDist(Body left, Body right)
{
    if (left == Undefined || right == Undefined) {
        return 0.0;
    }
    return PENALTY * (left != right);
}

static double modelDist(const char* left, const char* right)
{
    return PENALTY * !!strcmp(left, right);
}

double carDistance(const Car* left, const Car* right)
{
    /* TODO:
         tweak penalties,
         use body simularity matrix,
         use levenshtein distance for model names */

    return
        scalarDist(left->enginePower, right->enginePower) +
        scalarDist(left->maxSpeed, right->maxSpeed) +
        scalarDist(left->fuelConsumption, right->fuelConsumption) +
        bodyDist(left->body, right->body) +
        modelDist(left->model, right->model);
}
