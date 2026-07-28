/* void DrawSurvival() {
  BeginMode2D(camera1);

    ClearBackground(BLACK);

    DrawTextureRec(
      map1,
      (Rectangle) {
        map2Width / 2 + (player1.x + player1.width / 2) - screenWidth / 2,
        map2Height / 2 + (player1.y + player1.height / 2) - screenHeight / 2,
        screenWidth + offsetMappe * 2,
        screenHeight + offsetMappe * 2
      },
      (Vector2) {
        player1.x + player1.width / 2 - screenWidth / 2 - offsetMappe,
        player1.y + player1.height / 2 - screenHeight / 2 - offsetMappe
      },
      WHITE
    );

    for (int i = 0; i < kunais1->size; i++) {
      Kunai kunai = vectorGetKunais(kunais1, i);

      DrawTextureEx(
        player1.kunaiTexture,
        (Vector2) { kunai.x, kunai.y },
        atan2(kunai.yVel, kunai.xVel) * RAD2DEG,
        3.0,
        WHITE
      );
    }

    switch (player1.action) {
      case IDLE:;
        DrawTexturePro(
          player1.texture,
          (Rectangle) {
            0,
            0,
            67,
            72
          },
          (Rectangle) {
            player1.x,
            player1.y,
            player1.width,
            player1.height
          },
          (Vector2) {
            0,
            0
          },
          0.0f,
          WHITE
        );

        break;

      case RUNNING_RIGHT:;
        DrawTexturePro(
          player1.texture,
          (Rectangle) {
            floor(player1.runningFrame / (60 / fpsAnimazioneCamminata)) * -67,
            0,
            -67,
            72
          },
          (Rectangle) {
            player1.x,
            player1.y,
            player1.width,
            player1.height
          },
          (Vector2) {
            0,
            0
          },
          0.0f,
          WHITE
        );

        break;

      case RUNNING_LEFT:;
        DrawTexturePro(
          player1.texture,
          (Rectangle) {
            floor(player1.runningFrame / (60 / fpsAnimazioneCamminata)) * 67,
            0,
            67,
            72
          },
          (Rectangle) {
            player1.x,
            player1.y,
            player1.width,
            player1.height
          },
          (Vector2) {
            0,
            0
          },
          0.0f,
          WHITE
        );

        break;
      case THROWING_KUNAI:;
        DrawTexturePro(
          player1.attackTexture,
          (Rectangle) {
            floor(player1.throwingFrame / (60 / 15)) * 67,
            0,
            67,
            72
          },
          (Rectangle) {
            player1.x,
            player1.y,
            player1.width,
            player1.height
          },
          (Vector2) {
            0,
            0
          },
          0.0f,
          WHITE
        );

        break;
    }

    for (int i = 0; i < enemies1->size; i++) {
      Enemy enemy = vectorGetEnemies(enemies1, i);

      switch (enemy.typeEnemy) {
        case CIAMBELLA:;
          DrawTextureEx(
            ciambellaTexture,
            (Vector2) { enemy.x, enemy.y },
            0.0,
            3.0,
            WHITE
          );

          DrawRectangleLinesEx(
            (Rectangle) {
              enemy.x - 13,
              enemy.y - 23,
              enemy.width + 20 + 6,
              10 + 6
            },
            6,
            BLACK
          );
          DrawRectangle(enemy.x - 10, enemy.y - 20, ((enemy.width + 20) * enemy.vita) / 75, 10, RED);

          break;

        case CIAMBELLACHAD:;
          DrawTextureEx(
            ciambellaChadTexture,
            (Vector2) { enemy.x, enemy.y },
            0.0,
            1.0,
            WHITE
          );

          DrawRectangleLinesEx(
            (Rectangle) {
              enemy.x - 13,
              enemy.y - 23,
              enemy.width + 20 + 6,
              10 + 6
            },
            6,
            BLACK
          );
          DrawRectangle(enemy.x - 10, enemy.y - 20, ((enemy.width + 20) * enemy.vita) / 225, 10, RED);

          break;

        case CIAMBELLAKING:;
          DrawTextureEx(
            ciambellaKingTexture,
            (Vector2) { enemy.x, enemy.y },
            0.0,
            1.0,
            WHITE
          );

          DrawRectangleLinesEx(
            (Rectangle) {
              enemy.x - 13,
              enemy.y - 23,
              enemy.width + 20 + 6,
              10 + 6
            },
            6,
            BLACK
          );
          DrawRectangle(enemy.x - 10, enemy.y - 20, ((enemy.width + 20) * enemy.vita) / 450, 10, RED);

          break;
      }
    }

    DrawRectangleLinesEx(
      (Rectangle) {
        player1.x - 13,
        player1.y - 23,
        player1.width + 20 + 6,
        10 + 6
      },
      6,
      BLACK
    );
    DrawRectangle(player1.x - 10, player1.y - 20, ((player1.width + 20) * player1.vita) / 100, 10, GREEN);

  EndMode2D();
}

 */


// void DrawEndScore(unsigned long long totalTime) {
// 	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x5e5e5e5f));//darken bg
// 	//lost/win message
//     const char *result;

// 	if (/*score > sys.highscore &&*/ totalTime > bestSurvivedTime) result = "New Record!";
// 	/*else if (score > sys.highscore || totalTime > bestSurvivedTime) result = (score>sys.highscore) ? "New High Score!" : "New Best Time!";*/
// 	else result = "You can do better...";

// 	DrawTextSF(result, (screenWidth / 2) - (MeasureText(result, TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);
// 	//highscore
// 	DrawTextSF(TextFormat("High Score: %llu", bestScore), (screenWidth / 2) - (MeasureText(TextFormat("High Score: %llu", bestScore), subTitleFont) / 2), 250, subTitleFont, RED, BLACK, BLACK);
// 	//score
// 	DrawTextSF(TextFormat("Your score: %llu", player1.score), (screenWidth / 2) - (MeasureText(TextFormat("Your score: %llu", player1.score), subTitleFont) / 2), 320, subTitleFont, BLACK, BLACK, (player1.score > bestScore) ? RED : WHITE);
// 	//best time
// 	DrawTextSF(TextFormat("Best time: %02llu:%02llu", bestSurvivedTime / 60, bestSurvivedTime % 60), (screenWidth/2)-(MeasureText(TextFormat("Best time: %02d:%02d", floor(bestSurvivedTime / 60), bestSurvivedTime % 60), subTitleFont) / 2), 420, subTitleFont, RED, BLACK, BLACK);
// 	//time
// 	DrawTextSF(TextFormat("Your time: %02llu:%02llu", totalTime / 60, totalTime % 60),(screenWidth/2)-(MeasureText(TextFormat("Your time: %02d:%02d", floor(totalTime / 60), totalTime % 60), subTitleFont) / 2), 490, subTitleFont, BLACK, BLACK, (totalTime > bestSurvivedTime) ? RED : WHITE);

// 	//buttons
// 	//try again button
// 	DrawTextSF("Try Again",tryAgainBtn.x,tryAgainBtn.y,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,tryAgainBtn)?RED:WHITE);
// 	//exit button
// 	DrawTextSF("Go to Lobby",gotoLobbyBtn.x,gotoLobbyBtn.y,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,gotoLobbyBtn)?RED:WHITE);

// 	//mouse
// 	DrawTextureV(mouseTexture,(Vector2){mousePos.x-19,mousePos.y-19},WHITE);
// }
