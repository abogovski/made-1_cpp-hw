#include <gtest/gtest.h>

extern "C" {
#include "car.h"
}

#define EXPECT_CARS_EQ(left_, right_)\
    {\
        EXPECT_EQ(left_.enginePower, right_.enginePower);\
        EXPECT_EQ(left_.maxSpeed, right_.maxSpeed);\
        EXPECT_EQ(left_.fuelConsumption, right_.fuelConsumption);\
        EXPECT_EQ(left_.body, right_.body);\
        EXPECT_STREQ(left_.model, right_.model);\
    }

TEST(car, swapCars) {
    Car leftOriginal = {11., 12., 13., Minivan, "model1"};
    Car rightOriginal = {21., 22., 23., Hatchback, "model2"};

    Car left = leftOriginal;
    Car right = rightOriginal;

    swapCars(&left, &right);
    EXPECT_CARS_EQ(left, rightOriginal);
    EXPECT_CARS_EQ(right, leftOriginal);
}
