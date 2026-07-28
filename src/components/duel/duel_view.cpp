/* void DrawDuel() {
  BeginTextureMode(renderTexture1);

    ClearBackground(SKYBLUE);

    BeginMode2D(camera1);

      DrawTextureRec(
        map2,
        (Rectangle) {
          map2Width / 2 + (player1.x + player1.width / 2) - screenWidth / 4,
          map2Height / 2 + (player1.y + player1.height / 2) - screenHeight / 2,
          screenWidth / 2 + offsetMappe * 2,
          screenHeight + offsetMappe * 2
        },
        (Vector2) {
          player1.x + player1.width / 2 - screenWidth / 4 - offsetMappe,
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

  EndTextureMode();

  BeginTextureMode(renderTexture2);

    ClearBackground(GRAY);

    BeginMode2D(camera2);

      DrawTextureRec(
        map2,
        (Rectangle) {
          map2Width / 2 + (player2.x + player2.width / 2) - screenWidth / 4,
          map2Height / 2 + (player2.y + player2.height / 2) - screenHeight / 2,
          screenWidth / 2 + offsetMappe * 2,
          screenHeight + offsetMappe * 2
        },
        (Vector2) {
          player2.x + player2.width / 2 - screenWidth / 4 - offsetMappe,
          player2.y + player2.height / 2 - screenHeight / 2 - offsetMappe
        },
        WHITE
      );

      for (int i = 0; i < kunais2->size; i++) {
        Kunai kunai = vectorGetKunais(kunais2, i);

        DrawTextureEx(
          player2.kunaiTexture,
          (Vector2) { kunai.x, kunai.y },
          atan2(kunai.yVel, kunai.xVel) * RAD2DEG,
          3.0,
          WHITE
        );
      }

      switch (player2.action) {
        case IDLE:;
          DrawTexturePro(
            player2.texture,
            (Rectangle) {
              0,
              0,
              67,
              72
            },
            (Rectangle) {
              player2.x,
              player2.y,
              player2.width,
              player2.height
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
            player2.texture,
            (Rectangle) {
              floor(player2.runningFrame / (60 / fpsAnimazioneCamminata)) * -67,
              0,
              -67,
              72
            },
            (Rectangle) {
              player2.x,
              player2.y,
              player2.width,
              player2.height
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
            player2.texture,
            (Rectangle) {
              floor(player2.runningFrame / (60 / fpsAnimazioneCamminata)) * 67,
              0,
              67,
              72
            },
            (Rectangle) {
              player2.x,
              player2.y,
              player2.width,
              player2.height
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
            player2.attackTexture,
            (Rectangle) {
              floor(player2.throwingFrame / (60 / 15)) * 67,
              0,
              67,
              72
            },
            (Rectangle) {
              player2.x,
              player2.y,
              player2.width,
              player2.height
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

      for (int i = 0; i < enemies2->size; i++) {
        Enemy enemy = vectorGetEnemies(enemies2, i);

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
          player2.x - 13,
          player2.y - 23,
          player2.width + 20 + 6,
          10 + 6
        },
        6,
        BLACK
      );
      DrawRectangle(player2.x - 10, player2.y - 20, ((player2.width + 20) * player2.vita) / 100, 10, GREEN);

    EndMode2D();

  EndTextureMode();

  BeginDrawing();

    ClearBackground(WHITE);

    DrawTextureRec(renderTexture1.texture, (Rectangle) { 0.0f, 0.0f, (float) renderTexture1.texture.width, (float) -renderTexture1.texture.height }, (Vector2) { 0, 0 }, WHITE);
    DrawTextureRec(renderTexture2.texture, (Rectangle) { 0.0f, 0.0f, (float) renderTexture2.texture.width, (float) -renderTexture2.texture.height }, (Vector2) { screenWidth / 2.0f, 0 }, WHITE);

    DrawLineEx((Vector2) { screenWidth / 2 + 6, 0 }, (Vector2) { screenWidth / 2 + 6, screenHeight }, 12, RED);

    if (sys.setting) DrawSettingsPaused(sys);
    else if (sys.pause) DrawPause(mouseTexture);
    else if (player1.vita <= 0 || player2.vita <= 0) DrawEndDuel();

  EndDrawing();
}


void DrawEndDuel() {
	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x5e5e5e5f));//darken bg

  //title
	DrawTextSF("End of the Duel!",(screenWidth / 2) - (MeasureText("End of the Duel!", TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);

  if (player1.vita > player2.vita) {
    //winner
    DrawTextSF("Player 1 has won the duel", (screenWidth / 2) - (MeasureText("Player 1 has won the duel", buttonFont) / 2), (screenHeight / 2) - 100, buttonFont, BLACK, BLACK, RED);

    //winner score
    DrawTextSF(TextFormat("with a total score of: %llu", player1.score), (screenWidth / 2) - (MeasureText(TextFormat("with a total score of: %llu", player1.score), buttonFont) / 2), (screenHeight / 2) - 50, buttonFont, BLACK, BLACK, RED);

    //loser
    DrawTextSF("Player 2 has lost the duel", (screenWidth / 2) - (MeasureText("Player 2 has lost the duel", buttonFont) / 2), (screenHeight / 2) + 50, buttonFont, BLACK, BLACK, GetColor(0x2d63baff));

    //loser score
    DrawTextSF(TextFormat("with a total score of: %llu", player2.score), (screenWidth / 2) - (MeasureText(TextFormat("with a total score of: %llu", player2.score), buttonFont) / 2), (screenHeight / 2) + 100, buttonFont, BLACK, BLACK, GetColor(0x2d63baff));
  } else if (player1.vita < player2.vita) {
    //winner
    DrawTextSF("Player 2 has won the duel", (screenWidth / 2) - (MeasureText("Player 2 has won the duel", buttonFont) / 2), (screenHeight / 2) - 100, buttonFont, BLACK, BLACK, GetColor(0x2d63baff));

    //winner score
    DrawTextSF(TextFormat("with a total score of: %llu", player2.score), (screenWidth / 2) - (MeasureText(TextFormat("with a total score of: %llu", player2.score), buttonFont) / 2), (screenHeight / 2) - 50, buttonFont, BLACK, BLACK, GetColor(0x2d63baff));

    //loser
    DrawTextSF("Player 1 has lost the duel", (screenWidth / 2) - (MeasureText("Player 1 has lost the duel", buttonFont) / 2), (screenHeight / 2) + 50, buttonFont, RED, BLACK, BLACK);

    //loser score
    DrawTextSF(TextFormat("with a total score of: %llu", player1.score), (screenWidth / 2) - (MeasureText(TextFormat("with a total score of: %llu", player1.score), buttonFont) / 2), (screenHeight / 2) + 100, buttonFont, BLACK, BLACK, RED);
  } else {
    DrawTextSF(TextFormat("It's a draw"), (screenWidth / 2) - (MeasureText("It's a draw", subTitleFont) / 2), (screenHeight / 2) - 200, subTitleFont, BLACK, BLACK, RED);

    DrawTextSF(TextFormat("Player 1 has a total score of: %llu", player1.score), (screenWidth / 2) - (MeasureText(TextFormat("Player 1 has a total score of: %llu", player1.score), buttonFont) / 2), (screenHeight / 2) - 100, buttonFont, BLACK, BLACK, RED);

    DrawTextSF(TextFormat("Player 2 has a total score of: %llu", player2.score), (screenWidth / 2) - (MeasureText(TextFormat("Player 2 has a total score of: %llu", player2.score), buttonFont) / 2), (screenHeight / 2) - 50, buttonFont, BLACK, BLACK, GetColor(0x2d63baff));
  }

	//buttons
	//play again button
	DrawTextSF("Play Again",playAgainBtn.x,playAgainBtn.y,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,playAgainBtn)?RED:WHITE);

  //exit button
	DrawTextSF("Go to Lobby",gotoLobbyBtn.x,gotoLobbyBtn.y,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,gotoLobbyBtn)?RED:WHITE);

	//mouse
	DrawTextureV(mouseTexture,(Vector2) { mousePos.x - 19, mousePos.y - 19 },WHITE);

}

*/
