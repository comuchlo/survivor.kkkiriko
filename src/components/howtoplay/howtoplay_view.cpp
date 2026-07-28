/*
void DrawHowToPlay() {
	DrawTextureEx(lobbyBg, (Vector2) { 0, 0 }, 0.0f, (float) screenWidth / 1920, WHITE);//bg
	DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(0x5e5e5e5f));//darken bg

	BeginMode2D(camera1);

		DrawTextSF("How to Play", (screenWidth / 2) - (MeasureText("How to Play", TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);
		DrawTextSF("Hi and welcome to 'Kiriko and the donuts!'", (screenWidth / 2) - (MeasureText("Hi and welcome to 'Kiriko and the donuts!'", subTitleFont) / 2), 250, subTitleFont, BLACK, BLACK, RED);

		DrawTextSF("Basic Commands:", 12, 350, subTitleFont, BLACK, BLACK, RED);
		DrawText("Use arrows or WASD to move in the menus and ENTER to confirm.", 15, 420, textFont, BLACK);
		DrawText("In order to exit the game whenever you want, you can always use alt+f4 ", 15, 450, textFont, BLACK);

		DrawTextSF("In-game Commands:", 12, 530, subTitleFont, BLACK, BLACK, RED);
		DrawTextSF("Pause:", 15, 600, textFont, BLACK, BLACK, RED);
		DrawText(" whenever you are in Training or Survival or Duel, you can always pause", 15 + MeasureText("Pause:", textFont), 600, textFont, BLACK);
		DrawText("the game using ESCAPE, you will then use the mouse to move around the menu,", 35, 630, textFont, BLACK);
		DrawText("enter again ESCAPE to quick resume.", 35, 660, textFont, BLACK);

		DrawTextSF("Training:", 15, 690, textFont, BLACK, BLACK, RED);
		DrawText(" here you can practice your aim with your mouse against", 15 + MeasureText("Training:", textFont), 690, textFont, BLACK);
		DrawText("the enemies (CLICK button enabled)", 35, 720, textFont, BLACK);

		DrawTextSF("Survival and Duel:", 15, 750, textFont, BLACK, BLACK, RED);
		DrawText(" these two games are endless PvE (Player vs Enemies),", 15 + MeasureText("Survival and Duel:", textFont), 750, textFont, BLACK);
		DrawText("hold on as long as you can for greater records!", 35, 780, textFont, BLACK);
		DrawText("As the endless says, there is no ending in it except in duel", 35, 810, textFont, BLACK);
		DrawText("when a player dies, the other wins.", 35, 840, textFont, BLACK);

		DrawTextSF("Have a great experience playing all of them!", (screenWidth / 2) - (MeasureText("Have a great experience playing all of them!", buttonFont) / 2), 910, buttonFont, BLACK, BLACK, RED);

 EndMode2D();
} */
