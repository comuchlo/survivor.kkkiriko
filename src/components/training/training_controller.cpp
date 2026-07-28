/* void InitTraining() {
  player1.x = -100;
  player1.y = -100;
  player1.width = 200;
  player1.height = 200;
  player1.vita = 100;
  player1.hitten = false;
  player1.hittenFrame = 0;
  player1.runningFrame = 0;
  player1.throwingFrame = 0;
  player1.score = 0;
  player1.action = IDLE;
  player1.xVel = playerSpeed;
  player1.yVel = playerSpeed;

  vectorClearEnemies(enemies1);
  vectorResizeEnemies(enemies1, 1);

  Enemy enemy;

  enemy.x = screenWidth / 2;
  enemy.y = 0;
  enemy.typeEnemy = CIAMBELLA;
  enemy.width = ciambellaSize * 3;
  enemy.height = ciambellaSize * 3;
  enemy.vita = 75;
  enemy.frameHit = 0;

  Vector2 vettoreVelocitaNemico = normalizeVector(
    (Vector2) {
      player1.x + player1.width / 2 - enemy.x + enemy.width / 2,
      player1.y + player1.height / 2 - enemy.y + enemy.height / 2
    }
  );

  enemy.xVel = vettoreVelocitaNemico.x * enemySpeed;
  enemy.yVel = vettoreVelocitaNemico.y * enemySpeed;

  enemy.oldRec = (Rectangle) {
    enemy.x,
    enemy.y,
    enemy.width,
    enemy.height
  };

  vectorPushEnemies(enemies1, enemy);

  vectorClearKunais(kunais1);
} */
