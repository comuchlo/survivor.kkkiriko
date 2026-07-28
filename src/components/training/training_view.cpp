/* void DrawTrainingSettings() {
  DrawRectangle(0,0,1920,1080,GetColor(0x000005f));//darken bg
  //settings body
  DrawRectangle(636,0,10,540,BLACK);//outerborder up2
  DrawRectangle(638,0,8,538,RED);//border up2
  DrawRectangle(1274,540,10,540,BLACK);//outerborder down2
  DrawRectangle(1274,542,8,538,RED);//border down2

  DrawRectangle(646,0,628,1080,BLACK);//outerbody
  DrawRectangle(651,0,618,1080,GRAY);//innerbody

  //title
  DrawTextSF("Training",(screenWidth / 2) - (MeasureText("Training", TitleFont) / 2) + 2,20,TitleFont,RED,BLACK,BLACK);
  DrawTextSF("options",(screenWidth / 2) - (MeasureText("options", subTitleFont) / 2) + 2,130,subTitleFont,RED,BLACK,BLACK);
  //line separator
  DrawLineEx((Vector2){659,225},(Vector2){1257,225},3,BLACK);
  DrawLineEx((Vector2){661,227},(Vector2){1259,227},3,RED);
  DrawLineEx((Vector2){663,229},(Vector2){1261,229},3,BLACK);

  int shiftDown=0;
  char temp[20];

  Enemy enemy = vectorGetEnemies(enemies1, 0);

  if (sys.setting<18) {//draw enemy opts
    //enemy
    DrawTextSF("Enemy",834,320,subTitleFont,(sys.setting==10)?RED:WHITE,BLACK,BLACK);
    if (sys.setting==10) {
      DrawArrowSF(764,330,buttonFont,buttonFont,5,1,BLACK,BLACK,RED);
      DrawArrowSF(1096,330,buttonFont,buttonFont,5,0,BLACK,BLACK,RED);
    }
    //type of enemy -> normal , king , gigachad
    DrawTextSF("type",900,420,buttonFont,BLACK,BLACK,(sys.setting==11)?RED:WHITE);
    if (sys.setting==11) {
      shiftDown=60;
      if (enemy.typeEnemy==CIAMBELLA) sprintf(temp,"Donut");
      else if (enemy.typeEnemy==CIAMBELLAKING) sprintf(temp,"King");
      else sprintf(temp,"Giga Donut");
      DrawTextSF(temp,960-(MeasureText(temp,textFont)/2),490,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(temp,textFont)/2),490,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(temp,textFont)/2),490,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //movement -> idle , follow
    DrawTextSF("movements",817,500+shiftDown,buttonFont,BLACK,BLACK,(sys.setting==12)?RED:WHITE);
    if (sys.setting==12) {
      shiftDown=60;
      sprintf(temp,(true)?"follow":"idle");
      DrawTextSF(temp,960-(MeasureText(temp,textFont)/2),570,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(temp,textFont)/2),570,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(temp,textFont)/2),570,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //hostile -> attack player , peaceful
    DrawTextSF("hostility",851,580+shiftDown,buttonFont,BLACK,BLACK,(sys.setting==13)?RED:WHITE);
    if (sys.setting==13) {
      shiftDown=60;
      sprintf(temp,(true)?"attack":"peaceful");
      DrawTextSF(temp,960-(MeasureText(temp,textFont)/2),650,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(temp,textFont)/2),650,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(temp,textFont)/2),650,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //health -> unlimited , normal
    DrawTextSF("health",875,660+shiftDown,buttonFont,BLACK,BLACK,(sys.setting==14)?RED:WHITE);
    if (sys.setting==14) {
      shiftDown=60;
      DrawTextSF(TextFormat("%d",enemy.vita),960-(MeasureText(TextFormat("%d",enemy.vita),textFont)/2),730,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(TextFormat("%d",enemy.vita),textFont)/2),730,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(TextFormat("%d",enemy.vita),textFont)/2),730,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //speed -> 0 ... normal ... megaspeed
    DrawTextSF("speed",880,740+shiftDown,buttonFont,BLACK,BLACK,(sys.setting==15)?RED:WHITE);
    if (sys.setting==15) {
      shiftDown=60;
      (eSpeedMultiplier>1.9)?sprintf(temp,"x%.1f",eSpeedMultiplier):sprintf(temp,"x%.2f",eSpeedMultiplier);
      DrawTextSF(temp,960-(MeasureText(temp,textFont)/2),810,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(temp,textFont)/2),810,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(temp,textFont)/2),810,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //reset settings
    DrawTextSF("reset settings",757,960,buttonFont,BLACK,BLACK,(sys.setting==16)?RED:WHITE);
    //exit
    DrawTextSF("exit",911,1020,buttonFont,BLACK,BLACK,(sys.setting==17)?RED:WHITE);
  } else {
    //player
    DrawTextSF("Player",821,320,subTitleFont,(sys.setting==18)?RED:WHITE,BLACK,BLACK);
    if (sys.setting==18) {
      DrawArrowSF(751,330,buttonFont,buttonFont,5,1,BLACK,BLACK,RED);
      DrawArrowSF(1109,330,buttonFont,buttonFont,5,0,BLACK,BLACK,RED);
    }
    //health
    DrawTextSF("health",875,500,buttonFont,BLACK,BLACK,(sys.setting==19)?RED:WHITE);
    if (sys.setting==19) {
      shiftDown=60;
      DrawTextSF(TextFormat("%d",player1.vita),960-(MeasureText(TextFormat("%d",player1.vita),textFont)/2),570,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(TextFormat("%d",player1.vita),textFont)/2),570,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(TextFormat("%d",player1.vita),textFont)/2),570,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //atk
    DrawTextSF("damage",864,580+shiftDown,buttonFont,BLACK,BLACK,(sys.setting==20)?RED:WHITE);
    if (sys.setting==20) {
      shiftDown=60;
      DrawTextSF(TextFormat("%d",kunaiDamage),960-(MeasureText(TextFormat("%d",kunaiDamage),textFont)/2),650,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(TextFormat("%d",kunaiDamage),textFont)/2),650,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(TextFormat("%d",kunaiDamage),textFont)/2),650,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //speed
    DrawTextSF("speed",880,660+shiftDown,buttonFont,BLACK,BLACK,(sys.setting==21)?RED:WHITE);
    if (sys.setting==21) {
      shiftDown=60;
      (pSpeedMultiplier>1.9)?sprintf(temp,"x%.1f",pSpeedMultiplier):sprintf(temp,"x%.2f",pSpeedMultiplier);
      DrawTextSF(temp,960-(MeasureText(temp,textFont)/2),730,textFont,BLACK,BLACK,RED);
      DrawArrowSF(914-(MeasureText(temp,textFont)/2),730,buttonFont-20,buttonFont-20,5,1,BLACK,BLACK,RED);
      DrawArrowSF(970+(MeasureText(temp,textFont)/2),730,buttonFont-20,buttonFont-20,5,0,BLACK,BLACK,RED);
    }
    //reset settings
    DrawTextSF("reset settings",757,960,buttonFont,BLACK,BLACK,(sys.setting==22)?RED:WHITE);
    //exit
    DrawTextSF("exit",911,1020,buttonFont,BLACK,BLACK,(sys.setting==23)?RED:WHITE);
  }//dimension [?]
}




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
