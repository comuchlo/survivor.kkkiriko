// void InitDuel() {
//   player1.x = screenWidth / 4 - 100;
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

//   player2.x = screenWidth / 4 - 100;
//   player2.y = screenHeight / 2 - 100;
//   player2.width = 200;
//   player2.height = 200;
//   player2.vita = 100;
//   player2.hitten = false;
//   player2.hittenFrame = 0;
//   player2.runningFrame = 0;
//   player2.throwingFrame = 0;
//   player2.score = 0;
//   player2.action = IDLE;
//   player2.xVel = playerSpeed;
//   player2.yVel = playerSpeed;
//   /*player2.oldRec = (Rectangle) {
//     player2.x,
//     player2.y,
//     player2.width,
//     player2.height
//   };*/

//   int randomEnemyX, randomEnemyY;
//   Enemy enemy;

//   vectorClearEnemies(enemies1);
//   vectorResizeEnemies(enemies1, 10);

//   for (int i = 0; i < enemies1->capacity; i++) {
//     do {
//       randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x);

//     do {
//       randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y);

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

//     vectorSetEnemies(enemies1, i, enemy);
//   }

//   vectorClearEnemies(enemies2);
//   vectorResizeEnemies(enemies2, 10);

//   for (int i = 0; i < enemies2->capacity; i++) {
//     do {
//       randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x);

//     do {
//       randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
//     } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y);

//     enemy.x = randomEnemyX;
//     enemy.y = randomEnemyY;
//     enemy.typeEnemy = CIAMBELLA;
//     enemy.width = ciambellaSize * 3;
//     enemy.height = ciambellaSize * 3;
//     enemy.vita = 75;
//     enemy.frameHit = 0;

//     Vector2 vettoreVelocitaNemico = normalizeVector(
//       (Vector2) {
//         player2.x + player2.width / 2 - enemy.x + enemy.width / 2,
//         player2.y + player2.height / 2 - enemy.y + enemy.height / 2
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

//     vectorSetEnemies(enemies2, i, enemy);
//   }

//   vectorClearKunais(kunais1);
//   vectorClearKunais(kunais2);
// }
