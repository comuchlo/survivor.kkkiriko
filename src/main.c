#include <raylib.h>
#include "../headers/game_manager.h"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  //init general
  InitWindow(0, 0, "Kiriko and the donuts");//FullScreen
  screenWidth = GetScreenWidth();//get FullScreen width
  screenHeight = GetScreenHeight();//get FullScreen height
  InitAudioDevice();
  HideCursor();

  Image icon = LoadImage("./textures/temp donut.png");
  SetWindowIcon(icon);

  bool initTraining = true, initDuel = true, initSurvival = true;

  srand(time(NULL));

  sys.choice = 1;
  sys.volume[0] = 75;
  sys.volume[1] = 50;
  sys.volume[2] = 70;
  sys.pause = false;
  sys.setting = 0;

  enemies1 = createVectorEnemies(1);
  enemies2 = createVectorEnemies(1);
  kunais1 = createVectorKunais(1);
  kunais2 = createVectorKunais(1);

  player1.texture = LoadTexture("./textures/Kiriko.png");
  player1.attackTexture = LoadTexture("./textures/animazione kunai.png");
  player1.kunaiTexture = LoadTexture("./textures/kunai.png");
  player2.texture = LoadTexture("./textures/Kiriko2.png");
  player2.attackTexture = LoadTexture("./textures/animazione kunai2.png");
  player2.kunaiTexture = LoadTexture("./textures/kunai2.png");

  idealScreen=LoadRenderTexture(1920,1080);
	actualScreen=(Rectangle){0,0,screenWidth,screenHeight};

  resumeBtn = (Rectangle) { (screenWidth / 2) - (MeasureText("Resume", subTitleFont) / 2) - 2, (screenHeight / 20) * 7 + 83, MeasureText("Resume", subTitleFont), buttonFont };
  trainingOptBtn = (Rectangle) { (screenWidth / 2) - (MeasureText("Training options", buttonFont) / 2) - 2, (screenHeight / 20) * 7 + 143, MeasureText("Training options", buttonFont), buttonFont };
  settingsBtn = (Rectangle) { (screenWidth / 2) - (MeasureText("Settings", subTitleFont) / 2) - 2, (screenHeight / 20) * 7 + 143, MeasureText("Settings", subTitleFont), buttonFont };
  exitBtn = (Rectangle) { (screenWidth / 2) - (MeasureText("Exit", subTitleFont) / 2) - 2, (screenHeight / 20) * 7 + 203, MeasureText("Exit", subTitleFont), buttonFont };
  tryAgainBtn = (Rectangle) { (screenWidth / 2) - ((MeasureText("Try Again", buttonFont) + MeasureText("Go to Lobby", buttonFont) + 50) / 2), screenHeight - 120, MeasureText("Try Again", buttonFont), buttonFont };
  playAgainBtn = (Rectangle) { (screenWidth / 2) - ((MeasureText("Play Again", buttonFont) + MeasureText("Go to Lobby", buttonFont) + 50) / 2), screenHeight - 120, MeasureText("Play Again", buttonFont), buttonFont };
  gotoLobbyBtn = (Rectangle) { (screenWidth / 2) + ((MeasureText("Try Again", buttonFont) + MeasureText("Go to Lobby", buttonFont) + 50) / 2) - MeasureText("Go to Lobby", buttonFont), screenHeight - 120, MeasureText("Go to Lobby", buttonFont), buttonFont };

  camera1 = (Camera2D) {
    (Vector2) { 0, 0 },
    (Vector2) { 0, 0 },
    0.0f,
    1.0f
  };
  camera2 = (Camera2D) {
    (Vector2) { 0, 0 },
    (Vector2) { 0, 0 },
    0.0f,
    1.0f
  };

  renderTexture1 = LoadRenderTexture(screenWidth / 2, screenHeight);
  renderTexture2 = LoadRenderTexture(screenWidth / 2, screenHeight);

  lobbyBg = LoadTexture("./textures/kirikobg2.png");

  map1 = LoadTexture("./textures/map1Complete.png");
  map2 = LoadTexture("./textures/map2Complete.png");

  trainingFloor = LoadTexture("./textures/dojo.png");
  mouseTexture = LoadTexture("./textures/temp mouse.png");

  ciambellaTexture = LoadTexture("./textures/temp donut.png");
  ciambellaChadTexture = LoadTexture("./textures/VeroChad.png");
  ciambellaKingTexture = LoadTexture("./textures/ciambella king.png");

  slash = LoadSound("./audio/slash.mp3");
  SetSoundVolume(slash, ((float) sys.volume[2]/100)*((float) sys.volume[0]/100));

  lobbyMusic = LoadMusicStream("./audio/temp lobby8bit.mp3");
	survivalMusic = LoadMusicStream("./audio/temp survival8bit.mp3");
	duelMusic = LoadMusicStream("./audio/temp duel8bit.mp3");

  currentSound = slash;//use currentSound to play all the sound with adjusted volume
	SetSoundVolume(currentSound, ((float) sys.volume[2] / 100) * ((float) sys.volume[0] / 100));

	//music
	currentMusic = lobbyMusic;//use currentMusic to play all the music with adjusted volume
	currentMusic.looping = true;

	SetMusicVolume(currentMusic, ((float) sys.volume[1] / 100) * ((float) sys.volume [0] / 100));
	PlayMusicStream(currentMusic);

  unsigned short int frameTimeSurvivalKunai = 0;
  unsigned int frameTimeSurvival = 0;
  unsigned long long survivedTime = 0;

  unsigned short int frameTimeDuelKunai = 0;
  unsigned int frameTimeDuel = 0;

  /*pthread_t threadCollisioneOrizzontale, threadCollisioneVerticale;*/

  SetTargetFPS(60);
  while (sys.choice != lobbyOpt * 10) {
    float deltaTime = GetFrameTime();

    UpdateMusicStream(currentMusic);

    if (sys.choice < 10) {//Lobby ------------------------------------
      camera1.offset = (Vector2) { 0, 0 };
      camera1.target = (Vector2) { 0, 0 };

      //events
      if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
          sys.choice--;
          if (sys.choice < 1) sys.choice = lobbyOpt;

          currentSound = slash;
          PlaySound(slash);
      }

      if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
          sys.choice++;
          if (sys.choice > lobbyOpt) sys.choice = 1;

          currentSound = slash;
          PlaySound(slash);
      }

      if (IsKeyPressed(KEY_ENTER)) {
        sys.choice *= 10;//confirm
      }
    } else if (sys.choice == 10) {//Training ------------------------
      if (initTraining) {
        InitTraining();

        camera1.offset = (Vector2) { screenWidth / 2, screenHeight / 2 };

        initTraining = false;
      }

      if (!sys.pause) {
        //update:
        //camera
        if (player1.x + player1.width / 2 < -screenWidth / 2 || player1.x + player1.width / 2 > screenWidth / 2)
          camera1.target.x = (player1.x < -screenWidth / 2) ? -screenWidth / 2 : screenWidth / 2;
        else
          camera1.target.x = player1.x + player1.width / 2;

        if (player1.y + player1.height / 2 < -screenHeight / 2 || player1.y + player1.height / 2 > screenHeight / 2)
          camera1.target.y = (player1.y < -screenHeight / 2) ? -screenHeight / 2 : screenHeight / 2;
        else
          camera1.target.y = player1.y + player1.height / 2;

        //mouse position camera
        mousePos = (Vector2) { GetMouseX() + (camera1.target.x - screenWidth / 2), GetMouseY() + (camera1.target.y - screenHeight / 2) };

        //events
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
          player1.y = MAX(-screenHeight, player1.y - (player1.yVel * deltaTime));
        }

        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
          player1.y = MIN(screenHeight - player1.height, player1.y + (player1.yVel * deltaTime));
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
          player1.x = MAX(-screenWidth, player1.x - (player1.xVel * deltaTime));
        }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
          player1.x = MIN(screenWidth - player1.width, player1.x + (player1.xVel * deltaTime));
        }

        Kunai kunai;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//click
          kunai.x = player1.x + player1.width / 2 - 16;
          kunai.y = player1.y + player1.height / 2 - 16;
          Vector2 kunaiDirection = normalizeVector((Vector2) { (float) mousePos.x - kunai.x + 16, (float) mousePos.y - kunai.y + 16 });
          kunai.xVel = kunaiDirection.x * kunaiSpeed;
          kunai.yVel = kunaiDirection.y * kunaiSpeed;

          vectorPushKunais(kunais1, kunai);
        }

        for (int i = 0; i < kunais1->size; i++) {
          kunai = vectorGetKunais(kunais1, i);

          vectorKunaisSetX(kunais1, (float) kunai.x + kunai.xVel * deltaTime, i);
          vectorKunaisSetY(kunais1, (float) kunai.y + kunai.yVel * deltaTime, i);
        }

        if (IsKeyReleased(KEY_ESCAPE)) {
          sys.pause = true;
        }
      } else {//gioco in pausa
        if (!sys.setting) {//se non su settings
          mousePos = (Vector2) { GetMouseX() - 38 / 2, GetMouseY() - 38 / 2 };

          if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
            sys.pause = false;
          } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, settingsBtn)) {//temporary goto settings
            sys.setting = 40;
          } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, exitBtn)) {//goto lobby
            sys.pause = false;
            sys.choice = 1;
            currentMusic = lobbyMusic;
            StopMusicStream(currentMusic);
            PlayMusicStream(currentMusic);
          }
        } else {//settings paused
          currentSound = slash;
          HandleSettingsEvents(&sys.setting, 0);
        }
      }
    } else if (sys.choice == 20) {//Duel ----------------------------
      if (initDuel) {
        InitDuel();

        camera1.offset = (Vector2) { screenWidth / 4, screenHeight / 2 };
        camera2.offset = (Vector2) { screenWidth / 4, screenHeight / 2 };

        initDuel = false;
      }

      if (!sys.pause && player1.vita > 0 && player2.vita > 0) {//se non e' in pausa
        Kunai kunai;
        Enemy enemy;

        if (frameTimeDuel == 60 * 35) {
          frameTimeDuel = 0;

          if (enemies1->size <= 50)
            SpawnNewEnemies(enemies1);
          if (enemies2->size <= 50)
            SpawnNewEnemies(enemies2);
        }

        camera1.target.x = player1.x + player1.width / 2;
        camera1.target.y = player1.y + player1.height / 2;

        camera1.rotation = 0;

        camera2.target.x = player2.x + player2.width / 2;
        camera2.target.y = player2.y + player2.height / 2;

        camera2.rotation = 0;

        frameTimeDuelKunai++;

        /*player1.oldRec = (Rectangle) {
          player1.x,
          player1.y,
          player1.width,
          player1.height
        };*/

        Vector2 vettoreVelocitaNemico;

        if (frameTimeDuelKunai == 120 - ((60 / 15) * 6)) {
          if (enemies1->size > 0)
            player1.action = THROWING_KUNAI;

          if (enemies2->size > 0)
            player2.action = THROWING_KUNAI;
        }

        if (frameTimeDuelKunai == 120) {
          if (enemies1->size > 0) {
            enemy = vectorGetEnemies(enemies1, 0);

            kunai.x = player1.x + player1.width / 2 - kunaiSize / 2;
            kunai.y = player1.y + player1.height / 2 - kunaiSize / 2;

            kunai.nearest = pitagora(
              (Vector2) {
                (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
                (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
              }
            );
            kunai.nearestIndex = 0;

            vectorPushKunais(kunais1, kunai);
          }

          if (enemies2->size > 0) {
            enemy = vectorGetEnemies(enemies1, 0);

            kunai.x = player2.x + player2.width / 2 - kunaiSize / 2;
            kunai.y = player2.y + player2.height / 2 - kunaiSize / 2;

            kunai.nearest = pitagora(
              (Vector2) {
                (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
                (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
              }
            );
            kunai.nearestIndex = 0;

            vectorPushKunais(kunais2, kunai);
          }

          frameTimeDuelKunai = 0;
        }

        if (player1.action != THROWING_KUNAI)
          player1.action = IDLE;

        if (player2.action != THROWING_KUNAI)
          player2.action = IDLE;

        if (player1.hittenFrame == 5) {
          player1.hitten = false;
          player1.hittenFrame = 0;
        }

        if (player1.hitten) {
          switch (rand() % 3) {
            case 0:;
              camera1.target = (Vector2) { camera1.target.x - 5, camera1.target.y };

              break;

            case 1:;
              camera1.target = (Vector2) { camera1.target.x + 5, camera1.target.y };

              break;

            case 2:;
              camera1.rotation = rand() % 4 - 2;

              break;
          }

          player1.hittenFrame++;
        }

        if (player2.hittenFrame == 5) {
          player2.hitten = false;
          player2.hittenFrame = 0;
        }

        if (player2.hitten) {
          switch (rand() % 3) {
            case 0:;
              camera2.target = (Vector2) { camera2.target.x - 5, camera2.target.y };

              break;

            case 1:;
              camera2.target = (Vector2) { camera2.target.x + 5, camera2.target.y };

              break;

            case 2:;
              camera2.rotation = rand() % 4 - 2;

              break;
          }

          player2.hittenFrame++;
        }

        for (int i = 0; i < enemies1->size; i++) {
          enemy = vectorGetEnemies(enemies1, i);

          if (enemy.frameHit >= 30)
            vectorEnemiesSetFrameHit(enemies1, 0, i);

          enemy = vectorGetEnemies(enemies1, i);

          if (
            CheckCollisionRecs(
              (Rectangle) {
                player1.x + 20,
                player1.y + 20,
                player1.width - 20,
                player1.height - 20
              },
              (Rectangle) {
                enemy.x,
                enemy.y,
                enemy.width,
                enemy.height
              }
            )
          ) {
            player1.hitten = true;

            switch (enemy.typeEnemy) {
              case CIAMBELLA:;
                if (enemy.frameHit == 0)
                  player1.vita -= 5;

                break;

              case CIAMBELLACHAD:;
                if (enemy.frameHit == 0)
                  player1.vita -= 10;

                break;

              case CIAMBELLAKING:;
                if (enemy.frameHit == 0)
                  player1.vita -= 15;

                break;
            }
          }

          vectorEnemiesSetFrameHit(enemies1, enemy.frameHit + 1, i);

          enemy = vectorGetEnemies(enemies1, i);

          /*vectorEnemiesSetOldRec(
            enemies1,
            (Rectangle) {
              enemy.x,
              enemy.y,
              enemy.width,
              enemy.height
            },
            i
          );*/

          enemy = vectorGetEnemies(enemies1, i);

          vettoreVelocitaNemico = normalizeVector(
            (Vector2) {
              player1.x + player1.width / 2 - enemy.x - enemy.width / 2,
              player1.y + player1.height / 2 - enemy.y - enemy.height / 2
            }
          );

          vectorEnemiesSetXVel(enemies1, (double) vettoreVelocitaNemico.x * enemySpeed, i);
          vectorEnemiesSetYVel(enemies1, (double) vettoreVelocitaNemico.y * enemySpeed, i);

          enemy = vectorGetEnemies(enemies1, i);

          vectorEnemiesSetX(enemies1, (float) enemy.x + enemy.xVel * deltaTime, i);

          /*ArgomentiCollisione argomentoCollisioneOrrizontale = (ArgomentiCollisione) {
            'o',
            i
          };

          pthread_create(&threadCollisioneOrizzontale, NULL, checkCollisionsEnemies, &argomentoCollisioneOrrizontale);*/

          enemy = vectorGetEnemies(enemies1, i);

          vectorEnemiesSetY(enemies1, (float) enemy.y + enemy.yVel * deltaTime, i);

          /*ArgomentiCollisione argomentoCollisioneVerticale = (ArgomentiCollisione) {
            'v',
            i
          };

          pthread_create(&threadCollisioneVerticale, NULL, checkCollisionsEnemies, &argomentoCollisioneVerticale);*/

          enemy = vectorGetEnemies(enemies1, i);

          /*pthread_join(threadCollisioneOrizzontale, NULL);
          pthread_join(threadCollisioneVerticale, NULL);*/

          for (int j = 0; j < kunais1->size; j++) {
            kunai = vectorGetKunais(kunais1, j);

            double distanzaNemicoKunai = pitagora((Vector2) {
              (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
              (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
            });

            if (kunai.nearest > distanzaNemicoKunai) {
              vectorKunaisSetNearest(kunais1, distanzaNemicoKunai, j);

              vectorKunaisSetNearestIndex(kunais1, i, j);
            }
          }
        }

        for (int i = 0; i < enemies2->size; i++) {
          enemy = vectorGetEnemies(enemies2, i);

          if (enemy.frameHit >= 30)
            vectorEnemiesSetFrameHit(enemies2, 0, i);

          enemy = vectorGetEnemies(enemies2, i);

          if (
            CheckCollisionRecs(
              (Rectangle) {
                player2.x + 20,
                player2.y + 20,
                player2.width - 20,
                player2.height - 20
              },
              (Rectangle) {
                enemy.x,
                enemy.y,
                enemy.width,
                enemy.height
              }
            )
          ) {
            player2.hitten = true;

            switch (enemy.typeEnemy) {
              case CIAMBELLA:;
                if (enemy.frameHit == 0)
                  player2.vita -= 5;

                break;

              case CIAMBELLACHAD:;
                if (enemy.frameHit == 0)
                  player2.vita -= 10;

                break;

              case CIAMBELLAKING:;
                if (enemy.frameHit == 0)
                  player2.vita -= 15;

                break;
            }
          }

          vectorEnemiesSetFrameHit(enemies2, enemy.frameHit + 1, i);

          enemy = vectorGetEnemies(enemies2, i);

          /*vectorEnemiesSetOldRec(
            enemies2,
            (Rectangle) {
              enemy.x,
              enemy.y,
              enemy.width,
              enemy.height
            },
            i
          );*/

          enemy = vectorGetEnemies(enemies2, i);

          vettoreVelocitaNemico = normalizeVector(
            (Vector2) {
              player2.x + player2.width / 2 - enemy.x - enemy.width / 2,
              player2.y + player2.height / 2 - enemy.y - enemy.height / 2
            }
          );

          vectorEnemiesSetXVel(enemies2, (double) vettoreVelocitaNemico.x * enemySpeed, i);
          vectorEnemiesSetYVel(enemies2, (double) vettoreVelocitaNemico.y * enemySpeed, i);

          enemy = vectorGetEnemies(enemies2, i);

          vectorEnemiesSetX(enemies2, (float) enemy.x + enemy.xVel * deltaTime, i);

          /*ArgomentiCollisione argomentoCollisioneOrrizontale = (ArgomentiCollisione) {
            'o',
            i
          };

          pthread_create(&threadCollisioneOrizzontale, NULL, checkCollisionsEnemies, &argomentoCollisioneOrrizontale);*/

          enemy = vectorGetEnemies(enemies2, i);

          vectorEnemiesSetY(enemies2, (float) enemy.y + enemy.yVel * deltaTime, i);

          /*ArgomentiCollisione argomentoCollisioneVerticale = (ArgomentiCollisione) {
            'v',
            i
          };

          pthread_create(&threadCollisioneVerticale, NULL, checkCollisionsEnemies, &argomentoCollisioneVerticale);*/

          enemy = vectorGetEnemies(enemies2, i);

          /*pthread_join(threadCollisioneOrizzontale, NULL);
          pthread_join(threadCollisioneVerticale, NULL);*/

          Kunai kunai;

          for (int j = 0; j < kunais2->size; j++) {
            kunai = vectorGetKunais(kunais2, j);

            double distanzaNemicoKunai = pitagora((Vector2) {
              (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
              (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
            });

            if (kunai.nearest > distanzaNemicoKunai) {
              vectorKunaisSetNearest(kunais2, distanzaNemicoKunai, j);

              vectorKunaisSetNearestIndex(kunais2, i, j);
            }
          }
        }

        for (int i = 0; i < kunais1->size; i++) {
          kunai = vectorGetKunais(kunais1, i);
          enemy = vectorGetEnemies(enemies1, kunai.nearestIndex);

          Vector2 vettoreVelocitaKunai = normalizeVector((Vector2) {
            (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
            (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
          });

          vectorKunaisSetXVel(kunais1, (double) vettoreVelocitaKunai.x * kunaiSpeed, i);
          vectorKunaisSetYVel(kunais1, (double) vettoreVelocitaKunai.y * kunaiSpeed, i);

          vectorKunaisSetX(kunais1, (float) kunai.x + kunai.xVel * deltaTime, i);
          vectorKunaisSetY(kunais1, (float) kunai.y + kunai.yVel * deltaTime, i);

          if (CheckCollisionRecs((Rectangle) { kunai.x, kunai.y, kunaiSize, kunaiSize }, (Rectangle) { enemy.x, enemy.y, enemy.width, enemy.height })) {
            vectorEnemiesSetVita(enemies1, enemy.vita - kunaiDamage, kunai.nearestIndex);

            vectorPopIndexKunais(kunais1, i);
          }
        }

        for (int i = 0; i < kunais2->size; i++) {
          kunai = vectorGetKunais(kunais2, i);
          enemy = vectorGetEnemies(enemies2, kunai.nearestIndex);

          Vector2 vettoreVelocitaKunai = normalizeVector((Vector2) {
            (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
            (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
          });

          vectorKunaisSetXVel(kunais2, (double) vettoreVelocitaKunai.x * kunaiSpeed, i);
          vectorKunaisSetYVel(kunais2, (double) vettoreVelocitaKunai.y * kunaiSpeed, i);

          vectorKunaisSetX(kunais2, (float) kunai.x + kunai.xVel * deltaTime, i);
          vectorKunaisSetY(kunais2, (float) kunai.y + kunai.yVel * deltaTime, i);

          if (CheckCollisionRecs((Rectangle) { kunai.x, kunai.y, kunaiSize, kunaiSize }, (Rectangle) { enemy.x, enemy.y, enemy.width, enemy.height })) {
            vectorEnemiesSetVita(enemies2, enemy.vita - kunaiDamage, kunai.nearestIndex);

            vectorPopIndexKunais(kunais2, i);
          }
        }

        for (int i = 0; i < enemies1->size; i++) {
          enemy = vectorGetEnemies(enemies1, i);

          if (enemy.vita <= 0) {
            switch (enemy.typeEnemy) {
              case CIAMBELLA:;
                player1.score += 5;

                break;

              case CIAMBELLACHAD:;
                player1.score += 10;

                break;

              case CIAMBELLAKING:;
                player1.score += 15;

                break;
            }

            vectorPopIndexEnemies(enemies1, i);
          }
        }

        for (int i = 0; i < enemies2->size; i++) {
          enemy = vectorGetEnemies(enemies2, i);

          if (enemy.vita <= 0) {
            switch (enemy.typeEnemy) {
              case CIAMBELLA:;
                player2.score += 5;

                break;

              case CIAMBELLACHAD:;
                player2.score += 10;

                break;

              case CIAMBELLAKING:;
                player2.score += 15;

                break;
            }

            vectorPopIndexEnemies(enemies2, i);
          }
        }

        // region:    --- Player1 movements

        if (IsKeyDown(KEY_W)) {
          player1.y -= player1.yVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_LEFT;
        }

        if (IsKeyDown(KEY_S)) {
          player1.y += player1.yVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_RIGHT;
        }

        if (IsKeyDown(KEY_A)) {
          player1.x -= player1.xVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_LEFT;
        }

        if (IsKeyDown(KEY_D)) {
          player1.x += player1.xVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_RIGHT;
        }

        switch (player1.action) {
          case IDLE:;
            player1.runningFrame = 0;

            break;
          case RUNNING_RIGHT:;
            if (player1.runningFrame == (60 / fpsAnimazioneCamminata) * frameAnimazioneCamminata)
              player1.runningFrame = 0;

            player1.runningFrame++;

            break;
          case RUNNING_LEFT:;
            if (player1.runningFrame == (60 / fpsAnimazioneCamminata) * frameAnimazioneCamminata)
              player1.runningFrame = 0;

            player1.runningFrame++;

            break;
          case THROWING_KUNAI:;
            if (player1.throwingFrame == (60 / 15) * 10) {
              player1.throwingFrame = 0;

              player1.action = IDLE;
            }

            player1.throwingFrame++;

            break;
        }

        // endregion: --- Player1 movements

        // region:    --- Player2 movements

        if (IsKeyDown(KEY_UP)) {
          player2.y -= player2.yVel * deltaTime;

          if (player2.action != THROWING_KUNAI)
            player2.action = RUNNING_LEFT;
        }

        if (IsKeyDown(KEY_DOWN)) {
          player2.y += player2.yVel * deltaTime;

          if (player2.action != THROWING_KUNAI)
            player2.action = RUNNING_RIGHT;
        }

        if (IsKeyDown(KEY_LEFT)) {
          player2.x -= player2.xVel * deltaTime;

          if (player2.action != THROWING_KUNAI)
            player2.action = RUNNING_LEFT;
        }

        if (IsKeyDown(KEY_RIGHT)) {
          player2.x += player2.xVel * deltaTime;

          if (player2.action != THROWING_KUNAI)
            player2.action = RUNNING_RIGHT;
        }

        switch (player2.action) {
          case IDLE:;
            player2.runningFrame = 0;

            break;
          case RUNNING_RIGHT:;
            if (player2.runningFrame == (60 / fpsAnimazioneCamminata) * frameAnimazioneCamminata)
              player2.runningFrame = 0;

            player2.runningFrame++;

            break;
          case RUNNING_LEFT:;
            if (player2.runningFrame == (60 / fpsAnimazioneCamminata) * frameAnimazioneCamminata)
              player2.runningFrame = 0;

            player2.runningFrame++;

            break;
          case THROWING_KUNAI:;
            if (player2.throwingFrame == (60 / 15) * 10) {
              player2.throwingFrame = 0;

              player2.action = IDLE;
            }

            player2.throwingFrame++;

            break;
        }

        // endregion: --- Player2 movements

        frameTimeDuel++;

        if (IsKeyReleased(KEY_ESCAPE)) {
          sys.pause = true;
        }
      } else if (sys.pause) {//gioco in pausa
        if (!sys.setting) {//se non su settings
          mousePos = (Vector2) { GetMouseX() - 38 / 2, GetMouseY() - 38 / 2 };

          if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
            sys.pause = false;
          } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, settingsBtn)) {//temporary goto settings
            sys.setting = 40;
          } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, exitBtn)) {//goto lobby
            initDuel = true;
            sys.pause = false;
            sys.choice = 1;
            currentMusic = lobbyMusic;
            StopMusicStream(currentMusic);
            PlayMusicStream(currentMusic);
          }
        } else {//settings paused
          currentSound = slash;
          HandleSettingsEvents(&sys.setting, 0);
        }
      } else {
        mousePos = (Vector2) { GetMouseX() - 19, GetMouseY() - 19 };

        //if clicked a button
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (CheckCollisionPointRec(mousePos, tryAgainBtn) || CheckCollisionPointRec(mousePos, gotoLobbyBtn))) {
          if (CheckCollisionPointRec(mousePos, tryAgainBtn)) {//tryAgainBtn
            initDuel = true;//goto setup survival -> reboot survival
          } else {//gotoLobbyBtn
            sys.choice = 2;
            StopMusicStream(currentMusic);
            currentMusic = lobbyMusic;
            PlayMusicStream(currentMusic);
          }
        }
      }
    } else if (sys.choice == 30) {//Survival ------------------------
      if (initSurvival) {
        InitSurvival();

        camera1.offset = (Vector2) { screenWidth / 2, screenHeight / 2 };
        frameTimeSurvivalKunai = 0;
        frameTimeSurvival = 0;
        survivedTime = 0;

        initSurvival = false;
      }

      if (!sys.pause && player1.vita > 0) {
        if (frameTimeSurvival % 60 == 0)
          survivedTime += 1;

        if (frameTimeSurvival == 60 * 35) {
          frameTimeSurvival = 0;

          if (enemies1->size <= 50)
            SpawnNewEnemies(enemies1);
        }

        camera1.target.x = player1.x + player1.width / 2;
        camera1.target.y = player1.y + player1.height / 2;

        camera1.rotation = 0;

        frameTimeSurvivalKunai++;

        /*player1.oldRec = (Rectangle) {
          player1.x,
          player1.y,
          player1.width,
          player1.height
        };*/

        Vector2 vettoreVelocitaNemico;

        if (frameTimeSurvivalKunai == 120 - ((60 / 15) * 6) && enemies1->size > 0)
          player1.action = THROWING_KUNAI;

        if (frameTimeSurvivalKunai == 120) {
          if (enemies1->size > 0) {
            Kunai kunai;
            Enemy enemy = vectorGetEnemies(enemies1, 0);

            kunai.x = player1.x + player1.width / 2 - kunaiSize / 2;
            kunai.y = player1.y + player1.height / 2 - kunaiSize / 2;

            kunai.nearest = pitagora(
              (Vector2) {
                (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
                (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
              }
            );
            kunai.nearestIndex = 0;

            vectorPushKunais(kunais1, kunai);
          }

          frameTimeSurvivalKunai = 0;
        }

        if (player1.action != THROWING_KUNAI)
          player1.action = IDLE;

        if (player1.hittenFrame == 5) {
          player1.hitten = false;
          player1.hittenFrame = 0;
        }

        if (player1.hitten) {
          switch (rand() % 3) {
            case 0:;
              camera1.target = (Vector2) { camera1.target.x - 5, camera1.target.y };

              break;

            case 1:;
              camera1.target = (Vector2) { camera1.target.x + 5, camera1.target.y };

              break;

            case 2:;
              camera1.rotation = rand() % 4 - 2;

              break;
          }

          player1.hittenFrame++;
        }

        Enemy enemy;

        for (int i = 0; i < enemies1->size; i++) {
          enemy = vectorGetEnemies(enemies1, i);

          if (enemy.frameHit >= 30) {
            vectorEnemiesSetHitted(enemies1, false, i);

            vectorEnemiesSetFrameHit(enemies1, 0, i);
          }

          enemy = vectorGetEnemies(enemies1, i);

          if (
            CheckCollisionRecs(
              (Rectangle) {
                player1.x + 20,
                player1.y + 20,
                player1.width - 20,
                player1.height - 20
              },
              (Rectangle) {
                enemy.x,
                enemy.y,
                enemy.width,
                enemy.height
              }
            )
          ) {
            player1.hitten = true;

            switch (enemy.typeEnemy) {
              case CIAMBELLA:;
                if (enemy.frameHit == 0) {
                  vectorEnemiesSetHitted(enemies1, true, i);

                  player1.vita -= 5;
                }

                break;

              case CIAMBELLACHAD:;
                if (enemy.frameHit == 0) {
                  vectorEnemiesSetHitted(enemies1, true, i);

                  player1.vita -= 10;
                }

                break;

              case CIAMBELLAKING:;
                if (enemy.frameHit == 0) {
                  vectorEnemiesSetHitted(enemies1, true, i);

                  player1.vita -= 15;
                }

                break;
            }
          }

          enemy = vectorGetEnemies(enemies1, i);

          if (enemy.hitted)
            vectorEnemiesSetFrameHit(enemies1, enemy.frameHit + 1, i);

          enemy = vectorGetEnemies(enemies1, i);

          /*vectorEnemiesSetOldRec(
            enemies1,
            (Rectangle) {
              enemy.x,
              enemy.y,
              enemy.width,
              enemy.height
            },
            i
          );

          enemy = vectorGetEnemies(enemies1, i);*/

          vettoreVelocitaNemico = normalizeVector(
            (Vector2) {
              player1.x + player1.width / 2 - enemy.x - enemy.width / 2,
              player1.y + player1.height / 2 - enemy.y - enemy.height / 2
            }
          );

          vectorEnemiesSetXVel(enemies1, (double) vettoreVelocitaNemico.x * enemySpeed, i);
          vectorEnemiesSetYVel(enemies1, (double) vettoreVelocitaNemico.y * enemySpeed, i);

          enemy = vectorGetEnemies(enemies1, i);

          vectorEnemiesSetX(enemies1, (float) enemy.x + enemy.xVel * deltaTime, i);

          /*ArgomentiCollisione argomentoCollisioneOrrizontale = (ArgomentiCollisione) {
            'o',
            i
          };

          pthread_create(&threadCollisioneOrizzontale, NULL, checkCollisionsEnemies, &argomentoCollisioneOrrizontale);*/

          enemy = vectorGetEnemies(enemies1, i);

          vectorEnemiesSetY(enemies1, (float) enemy.y + enemy.yVel * deltaTime, i);

          /*ArgomentiCollisione argomentoCollisioneVerticale = (ArgomentiCollisione) {
            'v',
            i
          };

          pthread_create(&threadCollisioneVerticale, NULL, checkCollisionsEnemies, &argomentoCollisioneVerticale);*/

          enemy = vectorGetEnemies(enemies1, i);

          /*pthread_join(threadCollisioneOrizzontale, NULL);
          pthread_join(threadCollisioneVerticale, NULL);*/

          for (int j = 0; j < kunais1->size; j++) {
            Kunai kunai = vectorGetKunais(kunais1, j);

            double distanzaNemicoKunai = pitagora((Vector2) {
              (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
              (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
            });

            if (kunai.nearest > distanzaNemicoKunai) {
              vectorKunaisSetNearest(kunais1, distanzaNemicoKunai, j);

              vectorKunaisSetNearestIndex(kunais1, i, j);
            }
          }
        }

        for (int i = 0; i < kunais1->size; i++) {
          Kunai kunai = vectorGetKunais(kunais1, i);
          Enemy enemy = vectorGetEnemies(enemies1, kunai.nearestIndex);

          Vector2 vettoreVelocitaKunai = normalizeVector((Vector2) {
            (enemy.x + enemy.width / 2) - (kunai.x + kunaiSize / 2),
            (enemy.y + enemy.height / 2) - (kunai.y + kunaiSize / 2)
          });

          vectorKunaisSetXVel(kunais1, (double) vettoreVelocitaKunai.x * kunaiSpeed, i);
          vectorKunaisSetYVel(kunais1, (double) vettoreVelocitaKunai.y * kunaiSpeed, i);

          vectorKunaisSetX(kunais1, (float) kunai.x + kunai.xVel * deltaTime, i);
          vectorKunaisSetY(kunais1, (float) kunai.y + kunai.yVel * deltaTime, i);

          if (CheckCollisionRecs((Rectangle) { kunai.x, kunai.y, kunaiSize, kunaiSize }, (Rectangle) { enemy.x, enemy.y, enemy.width, enemy.height })) {
            vectorEnemiesSetVita(enemies1, enemy.vita - kunaiDamage, kunai.nearestIndex);

            vectorPopIndexKunais(kunais1, i);
          }
        }

        for (int i = 0; i < enemies1->size; i++) {
          Enemy enemy1 = vectorGetEnemies(enemies1, i);

          switch (enemy.typeEnemy) {
            case CIAMBELLA:;
              player1.score += 5;

              break;

            case CIAMBELLACHAD:;
              player1.score += 10;

              break;

            case CIAMBELLAKING:;
              player1.score += 15;

              break;
          }

          if (enemy1.vita <= 0) {
            vectorPopIndexEnemies(enemies1, i);
          }
        }

        if (IsKeyDown(KEY_W)) {
          player1.y -= player1.yVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_LEFT;
        }

        if (IsKeyDown(KEY_S)) {
          player1.y += player1.yVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_RIGHT;
        }

        if (IsKeyDown(KEY_A)) {
          player1.x -= player1.xVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_LEFT;
        }

        if (IsKeyDown(KEY_D)) {
          player1.x += player1.xVel * deltaTime;

          if (player1.action != THROWING_KUNAI)
            player1.action = RUNNING_RIGHT;
        }

        switch (player1.action) {
          case IDLE:;
            player1.runningFrame = 0;

            break;
          case RUNNING_RIGHT:;
            if (player1.runningFrame == (60 / fpsAnimazioneCamminata) * frameAnimazioneCamminata)
              player1.runningFrame = 0;

            player1.runningFrame++;

            break;
          case RUNNING_LEFT:;
            if (player1.runningFrame == (60 / fpsAnimazioneCamminata) * frameAnimazioneCamminata)
              player1.runningFrame = 0;

            player1.runningFrame++;

            break;
          case THROWING_KUNAI:;
            if (player1.throwingFrame == (60 / 15) * 10) {
              player1.throwingFrame = 0;

              player1.action = IDLE;
            }

            player1.throwingFrame++;

            break;
        }

        frameTimeSurvival += 1;

        if (IsKeyReleased(KEY_ESCAPE))
          sys.pause = true;
      } else if (sys.pause) {//gioco in pausa
        if (!sys.setting) {//se non su settings
          mousePos = (Vector2) { GetMouseX() + 38 / 2, GetMouseY() + 38 / 2 };

          if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
            sys.pause = false;
          } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, settingsBtn)) {//temporary goto settings
            sys.setting = 40;
          } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, exitBtn)) {//goto lobby
            initSurvival = true;
            sys.pause = false;
            sys.choice = 1;
            currentMusic = lobbyMusic;
            StopMusicStream(currentMusic);
            PlayMusicStream(currentMusic);
          }
        } else {//settings paused
          currentSound = slash;
          HandleSettingsEvents(&sys.setting, 0);
        }
      } else {
        mousePos = (Vector2) { GetMouseX() - 19, GetMouseY() - 19 };

        //if clicked a button
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (CheckCollisionPointRec(mousePos, tryAgainBtn) || CheckCollisionPointRec(mousePos, gotoLobbyBtn))) {
          if (CheckCollisionPointRec(mousePos, tryAgainBtn)) {//tryAgainBtn
            initSurvival = true;//goto setup survival -> reboot survival
          } else {//gotoLobbyBtn
            sys.choice = 3;
            StopMusicStream(currentMusic);
            currentMusic = lobbyMusic;
            PlayMusicStream(currentMusic);
          }

          //reset the highscore & best time
          if (player1.score > bestScore) bestScore = player1.score;
          if (survivedTime > bestSurvivedTime) bestSurvivedTime = survivedTime;
        }
      }
    } else if (sys.choice >= 40 && sys.choice <= 40 + settingsOpt) {//Setings -------------------------
      //update
      currentSound = slash;
      HandleSettingsEvents(&sys.choice, sys.pause);
    } else if (sys.choice == 50) {//how to play-------------------------------------
      //events
      if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {//up
        if (camera1.target.y > 0) camera1.target.y -= 5;
      }

      if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {//down
        if (camera1.target.y < 1000 - screenHeight) camera1.target.y += 5;
      }

      if (IsKeyPressed(KEY_ESCAPE)) {//confirm
        sys.choice = 5;
      }
    } else if (sys.choice == 60) {//credits------------------------------------------
      //update
      if (camera1.target.y < 1020) camera1.target.y += 30 * deltaTime;

      //events
      if (IsKeyPressed(KEY_ESCAPE)) {//goto lobby
        sys.choice = 6;
        //set lobby music
        StopMusicStream(currentMusic);
        currentMusic = lobbyMusic;
        PlayMusicStream(currentMusic);
      }
    }

    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4)) {//alt+f4 -> exit
			sys.choice = lobbyOpt * 10;
		}

    //Draw ---------------------------------------
    if (sys.choice < 10) {//Lobby
      BeginDrawing();

        DrawTextureEx(lobbyBg, (Vector2) { 0, 0 }, 0, (float) screenWidth / 1920, WHITE);//bg
        DrawLobby(sys.choice);//buttons

      EndDrawing();
    } else if (sys.choice == 10) {//Training
      BeginDrawing();

        DrawTraining();

        if (sys.setting) DrawSettingsPaused();
        else if (sys.pause) DrawTrainingSettings();

      EndDrawing();
    } else if (sys.choice == 20) {//Duel
      DrawDuel();
    } else if (sys.choice == 30) {//Survival
      BeginDrawing();

        DrawSurvival();

        if (sys.setting) DrawSettingsPaused();
        else if (sys.pause) DrawPause();
        else if (player1.vita <= 0) DrawEndScore(survivedTime);

      EndDrawing();
    } else if (sys.choice >= 40 && sys.choice <= 40 + settingsOpt) {//Settings
      BeginDrawing();

        DrawTextureEx(lobbyBg, (Vector2) { 0, 0 }, 0, 1, WHITE);//bg
        DrawSettings(sys.choice);

      EndDrawing();
    } else if (sys.choice == 50) {
      BeginDrawing();

        DrawHowToPlay();

      EndDrawing();
    } else if (sys.choice == 60) {
      BeginDrawing();

        DrawCredits();

      EndDrawing();
    }
  }

  //unload resources
  UnloadTexture(lobbyBg);
  UnloadTexture(trainingFloor);
  UnloadTexture(map1);
  UnloadTexture(map2);
  UnloadTexture(player1.texture);
  UnloadTexture(player2.texture);
  UnloadTexture(player1.attackTexture);
  UnloadTexture(player2.attackTexture);
  UnloadTexture(player1.kunaiTexture);
  UnloadTexture(player2.kunaiTexture);
  UnloadTexture(ciambellaTexture);
  UnloadTexture(ciambellaChadTexture);
  UnloadTexture(ciambellaKingTexture);

  UnloadRenderTexture(idealScreen);
  UnloadRenderTexture(renderTexture1);
  UnloadRenderTexture(renderTexture2);

  UnloadImage(icon);

  UnloadSound(slash);

  UnloadMusicStream(lobbyMusic);
  UnloadMusicStream(duelMusic);
  UnloadMusicStream(survivalMusic);

  CloseAudioDevice();

  vectorDeleteEnemies(enemies1);
  vectorDeleteEnemies(enemies2);
  vectorDeleteKunais(kunais1);
  vectorDeleteKunais(kunais2);

  CloseWindow();

  return 0;
}

// #include "headers/game_manager.h"

// int main() {
// 	//enable vsync (before InitWindow) -> better graphic performance
// 	SetConfigFlags(FLAG_VSYNC_HINT);
// 	//init general -------------------------------------------------------------------
//     InitWindow(0,0, "Kiriko and the donuts");//FullScreen
// 	ToggleFullscreen();
//     screenWidth=GetScreenWidth();//get FullScreen width
//     screenHeight=GetScreenHeight();//get FullScreen height
//     InitAudioDevice();
//     HideCursor();
//     //--------------------------------------------------------------------------------

//     //load var -----------------------------------------------------------------------
//     //img
// 	lobbyBg = LoadTexture("img/kiriko-bg.png");
// 	trainingFloor = LoadTexture("img/dojo.png");
// 	//textures
// 	donut = LoadTexture("textures/temp donut.png");
// 	kiriko = LoadTexture("textures/temp kiriko.png");
// 	mouseTexture = LoadTexture("textures/temp mouse.png");
// 	//sound
// 	slash = LoadSound("audio/slash.mp3");
// 	//music
// 	lobbyMusic = LoadMusicStream("audio/temp lobby8bit.mp3");
// 	survivalMusic = LoadMusicStream("audio/temp survival8bit.mp3");
// 	duelMusic = LoadMusicStream("audio/temp duel8bit.mp3");
//     //--------------------------------------------------------------------------------

// 	//init var -----------------------------------------------------------------------
// 	//sys
// 	sys=(System){1,{75,50,70},0,0};
// 	//pause
// 	resumeBtn=(Rectangle){(screenWidth/2)-(MeasureText("resume",subTitleFont)/2)-2,(screenHeight/20)*7+83,MeasureText("resume",subTitleFont),buttonFont};
// 	settingsBtn=(Rectangle){(screenWidth/2)-(MeasureText("settings",subTitleFont)/2)-2,(screenHeight/20)*7+143,MeasureText("settings",subTitleFont),buttonFont};
// 	exitBtn=(Rectangle){(screenWidth/2)-(MeasureText("exit",subTitleFont)/2)-2,(screenHeight/20)*7+203,MeasureText("exit",subTitleFont),buttonFont};
// 	//camera
// 	Camera2D camera={0};
//     camera.target=(Vector2){0,0};
//     camera.offset=(Vector2){0,0};
//     camera.rotation=0.0f;
//     camera.zoom=1.0f;
//     // temp var for player
// 	p_x=0;
// 	p_y=0;
// 	p_width=49;
// 	p_height=80;
// 	//sound
// 	currentSound=slash;//use currentSound to play all the sound with adjusted volume
// 	SetSoundVolume(currentSound, ((float)sys.volume[2]/100)*((float)sys.volume[0]/100));
// 	//music
// 	currentMusic = lobbyMusic;//use currentMusic to play all the music with adjusted volume
// 	currentMusic.looping=true;
// 	SetMusicVolume(currentMusic, ((float)sys.volume[1]/100)*((float)sys.volume[0]/100));
// 	PlayMusicStream(currentMusic);
// 	//--------------------------------------------------------------------------------

// 	SetTargetFPS(60);
//     while (sys.choice!=lobbyOpt*10) {
//     	//general update music
//     	UpdateMusicStream(currentMusic);

//         if (sys.choice<10) {//Lobby --------------------------------------------------
// 			//events
// 			if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
// 				sys.choice--;
// 				if (sys.choice<1) sys.choice=lobbyOpt;
// 				currentSound=slash;
// 				PlaySoundMulti(currentSound);
// 			}
// 			if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
// 				sys.choice++;
// 				if (sys.choice>lobbyOpt) sys.choice=1;
// 				currentSound=slash;
// 				PlaySoundMulti(currentSound);
// 			}
// 			if (IsKeyPressed(KEY_ENTER)) {//confirm
// 				sys.pause=sys.choice;
// 				sys.choice*=10;
// 			}

// 		} else if (sys.choice==10 || sys.choice==20 || sys.choice==30 || sys.choice==50 || sys.choice==60) {//setup modalities -------
// 			//disable pause
// 			sys.pause=0;
// 			//change music
// 			StopMusicStream(currentMusic);
// 			if (sys.choice==10 || sys.choice==50) currentMusic=lobbyMusic;
// 			else if (sys.choice==20) currentMusic=duelMusic;
// 			else currentMusic=survivalMusic;
// 			PlayMusicStream(currentMusic);
// 			//reset camera2D
// 			camera.target=(Vector2){0,0};
// 			//other setup (player xy).......
// 			p_x=0;
// 			p_y=0;
// 			//
// 			sys.choice++;

// 		} else if (sys.choice==11) {//Training ---------------------------------------
// 			if (!sys.pause) {//se non e' in pausa
// 				//update:
// 				//camera
// 				if (p_x < -(screenWidth/2) || p_x > (screenWidth/2)) {
// 					camera.target.x=(p_x < -(screenWidth/2))?-screenWidth:0;
// 				}
// 				else camera.target.x=p_x-(screenWidth/2);
// 				if (p_y < -(screenHeight/2) || p_y > (screenHeight/2)) {
// 					camera.target.y=(p_y < -(screenHeight/2))?-screenHeight:0;
// 				}
// 				else camera.target.y=p_y-(screenHeight/2);
// 				//mouse position camera
// 				mousePos=(Vector2) {GetMouseX()+camera.target.x,GetMouseY()+camera.target.y};

// 				//events
// 				if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
// 					p_y=MAX(-screenHeight,p_y-(200*GetFrameTime()));
// 				}
// 				if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
// 					p_y=MIN(screenHeight-p_height,p_y+(200*GetFrameTime()));
// 				}
// 				if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
// 					p_x=MIN(screenWidth-p_width,p_x+(200*GetFrameTime()));
// 				}
// 				if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
// 					p_x=MAX(-screenWidth,p_x-(200*GetFrameTime()));
// 				}
// 				if (IsKeyReleased(KEY_ESCAPE)) {
// 					sys.pause=sys.choice;
// 				}
// 				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//click

// 				}
// 			} else {//gioco in pausa
// 				if (!sys.setting) {//se non su settings
// 					mousePos=GetMousePosition();
// 					if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
// 						sys.pause=0;
// 					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,settingsBtn)) {//temporary goto settings
// 						sys.setting=40;
// 					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,exitBtn)) {//goto lobby
// 						sys.pause=0;
// 						sys.choice=1;
// 						currentMusic=lobbyMusic;
// 						StopMusicStream(currentMusic);
// 						PlayMusicStream(currentMusic);
// 					}
// 				} else {//settings paused
// 					currentSound=slash;
// 					HandleSettingsEvents(&sys.setting,0);
// 				}
// 			}

// 		} else if (sys.choice==21) {//Duel -------------------------------------------
// 			if (!sys.pause) {//se non e' in pausa
// 				//events
// 				if (IsKeyReleased(KEY_ESCAPE)) {
// 					sys.pause=sys.choice;
// 				}
// 			} else {//gioco in pausa
// 				if (!sys.setting) {//se non su settings
// 					mousePos=GetMousePosition();
// 					if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
// 						sys.pause=0;
// 					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,settingsBtn)) {//temporary goto settings
// 						sys.setting=40;
// 					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,exitBtn)) {//goto lobby
// 						sys.pause=0;
// 						sys.choice=1;
// 						currentMusic=lobbyMusic;
// 						StopMusicStream(currentMusic);
// 						PlayMusicStream(currentMusic);
// 					}
// 				} else {//settings paused
// 					currentSound=slash;
// 					HandleSettingsEvents(&sys.setting,0);
// 				}
// 			}
// 		} else if (sys.choice==31) {//Survival ---------------------------------------
// 			if (!sys.pause) {//se non e' in pausa
// 				//events
// 				if (IsKeyReleased(KEY_ESCAPE)) {
// 					sys.pause=sys.choice;
// 				}
// 			} else {//gioco in pausa
// 				if (!sys.setting) {//se non su settings
// 					mousePos=GetMousePosition();
// 					if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,resumeBtn)) || IsKeyReleased(KEY_ESCAPE)) {//resume
// 						sys.pause=0;
// 					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,settingsBtn)) {//temporary goto settings
// 						sys.setting=40;
// 					} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos,exitBtn)) {//goto lobby
// 						sys.pause=0;
// 						sys.choice=1;
// 						currentMusic=lobbyMusic;
// 						StopMusicStream(currentMusic);
// 						PlayMusicStream(currentMusic);
// 					}
// 				} else {//settings paused
// 					currentSound=slash;
// 					HandleSettingsEvents(&sys.setting,0);
// 				}
// 			}
// 		} else if (sys.choice>=40 && sys.choice<=40+settingsOpt) {//Settings ----------
// 			//events
// 			currentSound=slash;
// 			HandleSettingsEvents(&sys.choice,sys.pause);

// 		} else if (sys.choice==51) {//how to play-------------------------------------
// 			//events
// 			if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {//up
// 				if (camera.target.y>0) camera.target.y-=5;
// 			}
// 			if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {//down
// 				if (camera.target.y<1000-screenHeight) camera.target.y+=5;
// 			}
// 			if (IsKeyPressed(KEY_ESCAPE)) {//confirm
// 				sys.choice=5;
// 			}
// 		}else if (sys.choice==61) {//credits------------------------------------------
// 			//update
// 			if (camera.target.y<1020)camera.target.y+=30*GetFrameTime();
// 			//events
// 			if (IsKeyPressed(KEY_ESCAPE)) {//goto lobby
// 				sys.choice=6;
// 				//set lobby music
// 				StopMusicStream(currentMusic);
// 				currentMusic=lobbyMusic;
// 				PlayMusicStream(currentMusic);
// 			}
// 		}
// 		//general events -  -  -  -  -
// 		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyDown(KEY_F4)) {//alt+f4 -> exit
// 			sys.choice=lobbyOpt*10;
// 		}

//         BeginDrawing();//Draw --------------------------------------------------------
// 			ClearBackground(BLACK);
// 			if (sys.choice<10) DrawLobby();//lobby --- --- ---
// 			else if (sys.choice==11) {//Training --- --- --
// 				DrawTraining(camera);
// 				if (sys.setting) DrawSettingsPaused(sys,no_texture);//settings
// 				else if (sys.pause) DrawPause(mouseTexture);//pausa
// 			}
// 			else if (sys.choice==21) {//Duel --- --- ---
// 				DrawDuel();
// 				if (sys.setting) DrawSettingsPaused(sys,no_texture);//settings
// 				else if (sys.pause) DrawPause(mouseTexture);//pausa
// 			}
// 			else if (sys.choice==31) {//Survival --- --- ---
// 				DrawSurvival();
// 				if (sys.setting) DrawSettingsPaused(sys,no_texture);//settings
// 				else if (sys.pause) DrawPause(mouseTexture);//pausa
// 			}
// 			else if (sys.choice>=40 && sys.choice<=40+settingsOpt) DrawSettings(sys.choice,lobbyBg);//Settings
// 			else if (sys.choice==51) DrawHowToPlay(camera);
// 			else if (sys.choice==61) DrawCredits(camera);
//         EndDrawing();

//     }

//     //unload resources
//     UnloadTexture(lobbyBg);
//     UnloadTexture(donut);

//     UnloadMusicStream(lobbyMusic);
//     UnloadMusicStream(duelMusic);
//     UnloadMusicStream(survivalMusic);

//     UnloadSound(slash);

//     CloseWindow();

//     return 0;
// }
