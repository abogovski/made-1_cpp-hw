#pragma once

#include "matrix.h"

std::optional<Matrix> tryBroadcastTo(const Matrix& matrix, const Shape& shape);
