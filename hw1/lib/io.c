#include "io.h"
#include <stdlib.h>
#include <string.h>

size_t DEFAULT_BUF_SIZE = 8;
static const int BUF_GROWTH_FACTOR = 2;

static bool extendBuf(char** buf, size_t* capacity) {
     *capacity *= BUF_GROWTH_FACTOR;
     char* newBuf = realloc(*buf, *capacity);
     if (newBuf == NULL) {
         return false;
     }
     *buf = newBuf;
     return true;
}

static char* readLine(FILE* file) {
    size_t capacity = DEFAULT_BUF_SIZE;
    char* buf = (char*)malloc(capacity);
    if (buf == NULL) {
        return NULL;
    }

    size_t offset = 0;
    while (fgets(buf + offset, capacity - offset, file) != NULL) {
        offset += strlen(buf + offset);
        if (buf[offset - 1] == '\n') {
            break;
        }
        if (offset == capacity - 1 && !extendBuf(&buf, &capacity)) {
            free(buf); buf = NULL;
            return NULL;
        }
    }
    return buf;
}

bool readCar(FILE* file, struct Car* car) {
    char body[MAX_BODY_STR_LEN + 1];

    int rv = fscanf(
        file,
        "%lf%lf%lf%s",
        &car->enginePower,
        &car->maxSpeed,
        &car->fuelConsumption,
        body);

    if (rv != 4) {
        return false;
    }

    car->body = bodyFromString(body);

    if (car->model != NULL) {
        free(car->model); car->model = NULL;
    }
    car->model = readLine(file);
    if (car->model == NULL) {
        return false;
    }

    return true;
}

void printCar(FILE* file, const struct Car* car)
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
