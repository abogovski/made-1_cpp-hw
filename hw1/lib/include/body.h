#pragma once

/* Source: https://en.wikipedia.org/wiki/Car_body_style#Current_styles */
enum Body {
    Undefined,

    Buggy,
    Convertible,
    Coupe,
    FlowerCar,
    Hatchback,
    Hearse,
    Limousine,
    Microvan,
    Minivan,
    PanelVan,
    PanelTruck,
    PickupTruck,
    Roadster,
    ShootingBrake,
    StationWagon,
    TargaTop,
    Ute,
};

#define MAX_BODY_STR_LEN 13

enum Body bodyFromString(const char* string);
const char* bodyToString(enum Body value);
