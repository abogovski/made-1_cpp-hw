#include "car.h"
#include "io.h"
#include <assert.h>
#include <stdlib.h>

int main()
{
    Car targetCar = UNDEFINED_CAR;
    if (!readCar(stdin, &targetCar)) {
        return 1;
    }

    Car foundCar = UNDEFINED_CAR;
    if (!readCar(stdin, &foundCar)) {
        return 1;
    }

    double foundDist = carDistance(&targetCar, &foundCar);
    Car car = UNDEFINED_CAR;

    while (readCar(stdin, &car)) {
        double newDist = carDistance(&targetCar, &car);
        if (newDist < foundDist) {
           foundCar = car;
        }
    }

    printf("First best match: ");
    printCar(stdout, &foundCar);

    return 0;
}
