#include "body.h"
#include <string.h>

struct BodyRepr {
    enum Body value;
    const char* string;
};

static const struct BodyRepr BODY_REPRS[] = {
    {Buggy,         "buggy"},
    {Convertible,   "convertible"},
    {Coupe,         "coupe"},
    {FlowerCar,     "flowercar"},
    {Hatchback,     "hatchback"},
    {Hearse,        "hearse"},
    {Limousine,     "limousine"},
    {Microvan,      "microvan"},
    {Minivan,       "minivan"},
    {PanelVan,      "panelvan"},
    {PanelTruck,    "paneltruck"},
    {PickupTruck,   "pickuptruck"},
    {Roadster,      "roadster"},
    {ShootingBrake, "shootingbrake"},
    {StationWagon,  "stationwagon"},
    {TargaTop,      "targatop"},
    {Ute,           "ute"},

    {Undefined,     NULL}
};

enum Body bodyFromString(const char* string) {
    const struct BodyRepr* bodyRepr = BODY_REPRS;
    while (bodyRepr->string != NULL) {
        if (!strcmp(bodyRepr->string, string)) {
            break;
        }
    }
    return bodyRepr->value;;
}

const char* bodyToString(enum Body value) {
    const struct BodyRepr* bodyRepr = BODY_REPRS;
    while (bodyRepr->string != NULL) {
        if (bodyRepr->value == value) {
            break;
        }
    }
    return bodyRepr->string;
}
