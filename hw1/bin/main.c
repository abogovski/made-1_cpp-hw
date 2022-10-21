#include "car.h"
#include "io.h"
#include <assert.h>
#include <stdlib.h>

int main()
{
    struct Car target;
    target.model = NULL;
    if (!readCar(stdin, &target)) {
        return 1;
    }

    struct Car found;
    found.model = NULL;
    if (!readCar(stdin, &found)) {
        free(target.model); target.model = NULL;
        return 1;
    }

    double foundDist = carDistance(&target, &found);
    struct Car car;
    car.model = NULL;

    while (readCar(stdin, &car)) {
        double newDist = carDistance(&target, &car);
        if (newDist < foundDist) {
           swapCars(&found, &car);
        }
    }

    printf("First best match: ");
    printCar(stdout, &found);

    free(target.model); target.model = NULL;
    free(found.model); found.model = NULL;
    free(car.model); car.model = NULL;

    return 0;
}
