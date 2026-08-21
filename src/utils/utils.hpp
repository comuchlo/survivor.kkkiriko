#ifndef UTILS_HPP
#define UTILS_HPP

#include <raylib.h>
#include  <sys/stat.h>

double pitagora(Vector2 vettore);
Vector2 normalizeVector(Vector2 vettore);
bool fileExists(const char* name); // non basta file exist di raylib?

#endif
