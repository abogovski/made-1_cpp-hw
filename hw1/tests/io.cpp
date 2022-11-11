#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

extern "C" {
#include "io.h"
}

#define EXPECT_CAR_EQ(left_, right_)\
    {\
        EXPECT_EQ(left_.maxSpeed, right_.maxSpeed);\
        EXPECT_EQ(left_.fuelConsumption, right_.fuelConsumption);\
        EXPECT_EQ(left_.enginePower, right_.enginePower);\
        EXPECT_EQ(left_.body, right_.body);\
        EXPECT_STREQ(left_.model, right_.model);\
    }

TEST(io, readCar) {
    char buf[] = "11.0 12.5 13.0 minivan model1\n";
    FILE* file = fmemopen(buf, strlen(buf), "r");

    Car car = {};
    EXPECT_EQ(readCar(file, &car), true);
    EXPECT_CAR_EQ(car, (Car{11., 12.5, 13.0, Minivan, "model1"}));
    fclose(file); file = nullptr;
}

TEST(io, readCarFail) {
    char bufNumericFail[] = "11.0 abc 123.0 minivan model1\n";
    FILE* file = fmemopen(bufNumericFail, strlen(bufNumericFail), "r");

    Car car = {};
    EXPECT_EQ(readCar(file, &car), false);
    fclose(file); file = nullptr;

    char bufBadBodyFail[] = "11.0 12.0 13.0 unexpected model1\n";
    file = fmemopen(bufBadBodyFail, strlen(bufBadBodyFail), "r");

    EXPECT_EQ(readCar(file, &car), false);
    fclose(file); file = nullptr;

    char bufNoBodyFail[] = "11.0 12.0 13.0";
    file = fmemopen(bufNoBodyFail, strlen(bufNoBodyFail), "r");

    EXPECT_EQ(readCar(file, &car), false);
    fclose(file); file = nullptr;

    char bufModelFail[] = "11.0 12.0 13.0 minivan\n";
    file = fmemopen(bufModelFail, strlen(bufModelFail), "r");

    EXPECT_EQ(readCar(file, &car), false);
    fclose(file); file = nullptr;
}

TEST(io, readCarTruncatedModel) {
    char buf[] = "11.0 12.0 13.0 minivan model678901234567";
    FILE* file = fmemopen(buf, strlen(buf), "r");

    Car car = {};
    EXPECT_EQ(readCar(file, &car), true);
    EXPECT_CAR_EQ(car, (Car{11, 12, 13, Minivan, "model6789012345"}));
}

TEST(io, printCar) {
    char buf[128] = "";
    FILE* file = fmemopen(buf, 127, "w");

    Car car = {11., 12.5, 13., Minivan, "model1"};
    printCar(file, &car);

    fclose(file); file = nullptr;
    EXPECT_STREQ(buf, "11.000000 12.500000 13.000000 minivan model1\n");
}
