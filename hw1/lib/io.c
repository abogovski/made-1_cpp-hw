#include "io.h"
#include <string.h>
#include <ctype.h>

static bool readWord(FILE* file, char* word, size_t maxLen) {
    int c = fgetc(file);
    while (c != EOF && isspace(c)) {
        c = fgetc(file);
    }
    if (c == EOF) {
        word[0] = '\0';
        return false;
    }

    size_t offset = 0;
    while (c != EOF && !isspace(c) && offset < maxLen) {
        word[offset++] = c;
        c = fgetc(file);
    }
    word[offset] = '\0';

    while (c != EOF && !isspace(c)) {
        c = fgetc(file);
    }
    return true;
}

static Body readBody(FILE* file) {
    char body[MAX_BODY_STR_LEN + 1];
    if (!readWord(file, body, MAX_BODY_STR_LEN)) {
        return Undefined;
    }
    return bodyFromString(body);
}

bool readModel(FILE* file, char* model) {
    return readWord(file, model, MAX_MODEL_STR_LEN);
}

bool readCar(FILE* file, Car* car) {
    int rv = fscanf(
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
