
// void InitSurvival() {
//   player1.x = screenWidth / 2 - 100;
//   player1.y = screenHeight / 2 - 100;
//   player1.width = 200;
//   player1.height = 200;
//   player1.vita = 100;
//   player1.hitten = false;
//   player1.hittenFrame = 0;
//   player1.runningFrame = 0;
//   player1.throwingFrame = 0;
//   player1.score = 0;
//   player1.action = IDLE;
//   player1.xVel = playerSpeed;
//   player1.yVel = playerSpeed;
//   /*player1.oldRec = (Rectangle) {
//     player1.x,
//     player1.y,
//     player1.width,
//     player1.height
//   };*/

//   int randomEnemyX, randomEnemyY;
//   Enemy enemy;

//   vectorClearEnemies(enemies1);
//   vectorResizeEnemies(enemies1, 50);

//   for (int i = 0; i < 10; i++) {
//     do {
//       randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x + player1.width);

//     do {
//       randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y + player1.height);

//     enemy.x = randomEnemyX;
//     enemy.y = randomEnemyY;
//     enemy.typeEnemy = CIAMBELLA;
//     enemy.width = ciambellaSize * 3;
//     enemy.height = ciambellaSize * 3;
//     enemy.vita = 75;
//     enemy.frameHit = 0;

//     Vector2 vettoreVelocitaNemico = normalizeVector(
//       (Vector2) {
//         player1.x + player1.width / 2 - enemy.x + enemy.width / 2,
//         player1.y + player1.height / 2 - enemy.y + enemy.height / 2
//       }
//     );

//     enemy.xVel = vettoreVelocitaNemico.x * enemySpeed;
//     enemy.yVel = vettoreVelocitaNemico.y * enemySpeed;

//     enemy.oldRec = (Rectangle) {
//       enemy.x,
//       enemy.y,
//       enemy.width,
//       enemy.height
//     };

//     vectorPushEnemies(enemies1, enemy);
//   }

//   vectorClearKunais(kunais1);
// }

// void SpawnNewEnemies(VectorEnemies *enemies) {
//   int randomEnemyX, randomEnemyY;
//   unsigned short int randomEnemyType;
//   Enemy enemy;

//   for (int i = 0; i < 10; i++) {
//     do {
//       randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x);

//     do {
//       randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y);

//     enemy.x = randomEnemyX;
//     enemy.y = randomEnemyY;

//     randomEnemyType = rand() % 12 + 1;

//     if (randomEnemyType >= 1 && randomEnemyType <= 6) {
//       enemy.typeEnemy = CIAMBELLA;
//       enemy.width = ciambellaSize * 3;
//       enemy.height = ciambellaSize * 3;
//       enemy.vita = 75;
//     } else if (randomEnemyType > 6  && randomEnemyType <= 10) {
//       enemy.typeEnemy = CIAMBELLACHAD;
//       enemy.width = ciambellaChadWidth;
//       enemy.height = ciambellaChadHeight;
//       enemy.vita = 225;
//     } else {
//       enemy.typeEnemy = CIAMBELLAKING;
//       enemy.width = ciambellaKingSize;
//       enemy.height = ciambellaKingSize;
//       enemy.vita = 450;
//     }

//     Vector2 vettoreVelocitaNemico = normalizeVector(
//       (Vector2) {
//         player1.x + player1.width / 2 - enemy.x + enemy.width / 2,
//         player1.y + player1.height / 2 - enemy.y + enemy.height / 2
//       }
//     );

//     enemy.xVel = vettoreVelocitaNemico.x * enemySpeed;
//     enemy.yVel = vettoreVelocitaNemico.y * enemySpeed;

//     enemy.oldRec = (Rectangle) {
//       enemy.x,
//       enemy.y,
//       enemy.width,
//       enemy.height
//     };

//     vectorPushEnemies(enemies, enemy);
//   }
// }
