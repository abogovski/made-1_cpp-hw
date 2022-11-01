#pragma once

/* Source: https://en.wikipedia.org/wiki/Car_body_style#Current_styles */
typedef enum Body {
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
} Body;

#define MAX_BODY_STR_LEN 13

Body bodyFromString(const char* string);
const char* bodyToString(Body value);
