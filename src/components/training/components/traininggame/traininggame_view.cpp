#include "traininggame.hpp"
#include <raylib.h>

void TrainingGame::drawModality() {
    const float renderW = drawer->RENDER_WIDTH, renderH = drawer->RENDER_HEIGHT;

    BeginMode2D(game_manager->cameras[0]);
      //map
      DrawTexture(*this->trainingMap, -renderW, -renderH, WHITE);

      // player + kunais related
      game_manager->players[0].draw();

      // TODO: DRAW THE REST

    EndMode2D();
}
/*
void DrawTraining() {
  BeginMode2D(camera1);

    ClearBackground(BLACK);

    //map
    DrawTextureV(trainingFloor, (Vector2) { (float) - screenWidth, (float) - screenHeight }, WHITE);

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

    //player
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

    //mouse
    if(!sys.pause) DrawTextureV(mouseTexture, mousePos, WHITE);//mouse

  EndMode2D();
}

*/
