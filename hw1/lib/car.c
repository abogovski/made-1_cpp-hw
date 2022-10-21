#include "car.h"
#include <math.h>
#include <string.h>

#define PENALTY 1

void swapCars(struct Car* left, struct Car* right)
{
    struct Car car = *left;
    *left = *right;
    *right = car;
}

static double scalarDist(double left, double right)
{
    if (isnan(left) || isnan(right)) {
        return 0.0;
    }
    return fabs(left - right);
}

static double bodyDist(enum Body left, enum Body right)
{
    if (left == Undefined || right == Undefined) {
        return 0.0;
    }
    return PENALTY;
}

static double modelDist(const char* left, const char* right)
{
    return PENALTY * !!strcmp(left, right);
}

double carDistance(const struct Car* left, const struct Car* right)
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
