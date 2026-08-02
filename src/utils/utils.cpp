#include <raylib.h>
#include <math.h>

double pitagora(Vector2 vettore) {
  return sqrt(pow((double) (vettore.x), 2) + pow((double) (vettore.y), 2));
}

Vector2 normalizeVector(Vector2 vettore) {
  double ipotenusa = pitagora(vettore);

  if (ipotenusa > 0) {
    return (Vector2) { (float) (vettore.x / ipotenusa), (float) (vettore.y / ipotenusa) };
  } else {
    return (Vector2) { 0.0f, 0.0f };
  }
}
