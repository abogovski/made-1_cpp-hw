#include "body.h"
#include <string.h>

typedef struct BodyRepr {
    enum Body value;
    const char* string;
} BodyRepr;

static const BodyRepr BODY_REPRS[] = {
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

Body bodyFromString(const char* string) {
    for (const BodyRepr* bodyRepr = BODY_REPRS ; bodyRepr->string != NULL; ++bodyRepr) {
        if (!strcmp(bodyRepr->string, string)) {
            return bodyRepr->value;
        }
    }
    return Undefined;
}

const char* bodyToString(Body value) {
    for (const BodyRepr* bodyRepr = BODY_REPRS; bodyRepr->string != NULL; ++bodyRepr) {
        if (bodyRepr->value == value) {
            return bodyRepr->string;
        }
    }
    return NULL;
}
