#include "io.h"
#include <string.h>
#include <ctype.h>

#define STRINGIZE_NX(A) #A
#define _S(A) STRINGIZE_NX(A)

static void consumeTail(FILE* file) {
    int c = fgetc(file);
    while (!isspace(c)) {
        if (c == EOF) {
            return;
        }
        c = fgetc(file);
    }
    ungetc(c, file);
}

static Body readBody(FILE* file) {
    char body[MAX_BODY_STR_LEN + 1];
    int rv = fscanf_s(file, " %s", body, MAX_BODY_STR_LEN);
    if (rv != 1) {
        return Undefined;
    }
    consumeTail(file);
    return bodyFromString(body);
}

bool readModel(FILE* file, char* model) {
    int rv = fscanf_s(file, " %s", model, MAX_MODEL_STR_LEN);
    if (rv != 1) {
        return false;;
    }
    consumeTail(file);
    return true;
}

bool readCar(FILE* file, Car* car) {
    int rv = fscanf_s(
        file,
        "%lf%lf%lf",
        &car->enginePower,
        &car->maxSpeed,
        &car->fuelConsumption);

    if (rv != 3) {
        return false;
    }

    car->body = readBody(file);
    if (car->body == Undefined || !readModel(file, car->model)) {
        return false;
    }

    return true;
}

void printCar(FILE* file, const Car* car)
{
    fprintf(
        file,
        "%lf %lf %lf %s %s\n",
        car->enginePower,
        car->maxSpeed,
        car->fuelConsumption,
        bodyToString(car->body),
        car->model);
}
