#include <gtest/gtest.h>
#include <cmath>
#include <cstring>

extern "C" {
#include "car.h"
}

TEST(car, carDist) {
    Car original = {11., 12., 13., Minivan, "model1"};
    Car modified = {21., 22., 23., Hatchback, "model2"};

    EXPECT_EQ(carDistance(&original, &modified), 10 + 10 + 10 + 1 + 1);

    original.maxSpeed = NAN;
    modified.fuelConsumption = NAN;
    original.enginePower = NAN;
    modified.body = Undefined;
    strcpy(modified.model, original.model);

    EXPECT_EQ(carDistance(&original, &modified), 0);
}
