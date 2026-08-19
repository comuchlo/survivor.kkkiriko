#include "utils.hpp"
#include <raylib.h>
#include <sys/stat.h>
#include <cmath>

double pitagora(Vector2 vettore) {
  return std::sqrt((double) (vettore.x * vettore.x) + (double) (vettore.y * vettore.y));
}

Vector2 normalizeVector(Vector2 vettore) {
    double ipotenusa = pitagora(vettore);

    if (ipotenusa > 0) {
        float inv = (float)(1.0f / ipotenusa);
        return (Vector2){ vettore.x * inv, vettore.y * inv };
    } else {
        return (Vector2) { 0.0f, 0.0f };
    }
}

bool fileExists(const char* name) {
  struct stat buffer;
  return (stat (name, &buffer) == 0);
}
