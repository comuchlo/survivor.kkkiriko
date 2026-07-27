#include <stdio.h>
#include <raylib.h>
#include <vector>

enum class TypeEnemy {
  CIAMBELLA = 1,
  CIAMBELLACHAD,
  CIAMBELLAKING
};

typedef struct {
  float x, y;
  int width, height;
  int vita;
  double xVel, yVel;
  bool hitted;
  unsigned short frameHit;
  Rectangle oldRec;
  TypeEnemy typeEnemy;
  Texture2D texture;
} Enemy;
typedef struct {
  Enemy *data;
  int size;
  int capacity;
} VectorEnemies;

class Enemies{

};



Enemy vectorPopIndexEnemies(VectorEnemies *vec, int index) {
  if (index >= vec->capacity) printf("L'index e' fuori i limiti -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  Enemy returnValue = vec->data[index];

  for (int i = index; i < vec->size - 1; i++)
    vec->data[i] = vec->data[i + 1];

  vec->size -= 1;

  return returnValue;
}

Enemy vectorPopEnemies(VectorEnemies *vec) {
  Enemy returnValue = vec->data[--vec->size];

  return returnValue;
}

Enemy vectorGetEnemies(VectorEnemies *vec, int index) {
  if (index >= vec->capacity) printf("L'index supera il numero di capacita' -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  return vec->data[index];
}

void vectorSetEnemies(VectorEnemies *vec, int index, Enemy value) {

}

void vectorPushEnemies(VectorEnemies *vec, Enemy value) {

}

void vectorResizeEnemies(VectorEnemies *vec, int length) {

}

void vectorShrinkEnemies(VectorEnemies *vec) {

}

void vectorClearEnemies(VectorEnemies *vec) {

}

void vectorEnemiesSetX(VectorEnemies *vec, float x, int index) {
  vec->data[index].x = x;
}

void vectorEnemiesSetY(VectorEnemies *vec, float y, int index) {
  vec->data[index].y = y;
}

void vectorEnemiesSetWidth(VectorEnemies *vec, int width, int index) {
  vec->data[index].width = width;
}

void vectorEnemiesSetHeight(VectorEnemies *vec, int height, int index) {
  vec->data[index].height = height;
}

void vectorEnemiesSetVita(VectorEnemies *vec, int vita, int index) {
  vec->data[index].vita = vita;
}

void vectorEnemiesSetXVel(VectorEnemies *vec, double xVel, int index) {
  vec->data[index].xVel = xVel;
}

void vectorEnemiesSetYVel(VectorEnemies *vec, double yVel, int index) {
  vec->data[index].yVel = yVel;
}

void vectorEnemiesSetHitted(VectorEnemies *vec, bool hitted, int index) {
  vec->data[index].hitted = hitted;
}

void vectorEnemiesSetFrameHit(VectorEnemies *vec, unsigned short frameHit, int index) {
  vec->data[index].frameHit = frameHit;
}

void vectorEnemiesSetTypeEnemy(VectorEnemies *vec, TypeEnemy typeEnemy, int index) {
  vec->data[index].typeEnemy = typeEnemy;
}

void vectorEnemiesSetTexture(VectorEnemies *vec, Texture2D texture, int index) {
  vec->data[index].texture = texture;
}
