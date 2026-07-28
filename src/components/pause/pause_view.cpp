/* void DrawPause() {
	DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(0x000005f));//darken screen

	//pause body

	//DrawRectangle((screenWidth*0.4)-7,(screenHeight*0.35)-7,(screenWidth*0.15)+9,179,BLACK);//outerborder up1
	DrawRectangle((screenWidth * 0.4) - 12, (screenHeight * 0.35) - 12, (screenWidth * 0.1) + 14, 141.5, BLACK);//outerborder up2

	//DrawRectangle((screenWidth*0.4)-5,(screenHeight*0.35)-5,(screenWidth*0.15)+5,175,RED);//border up1
	DrawRectangle((screenWidth * 0.4) - 10, (screenHeight * 0.35) - 10, (screenWidth * 0.1) + 10, 137.5, RED);//border up2

	//DrawRectangle((screenWidth*0.45)-2,(screenHeight*0.35)+83,(screenWidth*0.15)+9,179,BLACK);//outerborder down1
	DrawRectangle((screenWidth * 0.5) - 2, (screenHeight * 0.35) + 125.5, (screenWidth * 0.1) + 14, 141.5, BLACK);//outerborder down2

	//DrawRectangle((screenWidth*0.45),(screenHeight*0.35)+85,(screenWidth*0.15)+5,175,RED);//border down1
	DrawRectangle(screenWidth * 0.5, (screenHeight * 0.35) + 127.5, (screenWidth * 0.1) + 10, 137.5, RED);//border down2

	DrawRectangle(screenWidth * 0.4, screenHeight * 0.35, screenWidth * 0.2, 255, BLACK);//outerbody
	DrawRectangle((screenWidth * 0.4) + 5, (screenHeight * 0.35) + 5, (screenWidth * 0.2) - 10, 245, GRAY);//innerbody

	//title
	DrawTextSF("Pause", (screenWidth / 2) - (MeasureText("Pause", subTitleFont) / 2) + 2, (screenHeight / 20) * 7 + 12, subTitleFont, RED, BLACK, BLACK);

  //pause line separator
	DrawLineEx((Vector2) { (float) (screenWidth / 10) * 4 + 10, (float) (screenHeight / 20) * 7 + 68 }, (Vector2) { (float) (screenWidth / 10) * 6 - 19, (float) (screenHeight / 20) * 7 + 68 }, 2, BLACK);
	DrawLineEx((Vector2) { (float) (screenWidth / 10) * 4 + 12, (float) (screenHeight / 20) * 7 + 70 }, (Vector2) { (float) (screenWidth / 10) * 6 - 17, (float) (screenHeight / 20) * 7 + 70 }, 2, RED);
	DrawLineEx((Vector2) { (float) (screenWidth / 10) * 4 + 14, (float) (screenHeight / 20) * 7 + 72 }, (Vector2) { (float) (screenWidth / 10) * 6 - 15, (float) (screenHeight / 20) * 7 + 72 }, 2, BLACK);

  //option resume
	DrawTextSF("Resume", (screenWidth / 2) - (MeasureText("Resume", buttonFont) / 2), (screenHeight / 20) * 7 + 85, buttonFont, BLACK, BLACK, CheckCollisionPointRec(mousePos, resumeBtn) ? RED : WHITE);

  //option settings
	DrawTextSF("Settings", (screenWidth / 2) - (MeasureText("Settings", buttonFont) / 2), (screenHeight / 20) * 7 + 145, buttonFont, BLACK, BLACK, CheckCollisionPointRec(mousePos, settingsBtn) ? RED : WHITE);

  //option exit
	DrawTextSF("Exit", (screenWidth / 2) - (MeasureText("Exit", buttonFont) / 2), (screenHeight / 20) * 7 + 205, buttonFont, BLACK, BLACK, CheckCollisionPointRec(mousePos, exitBtn) ? RED : WHITE);

  //mouse
	DrawTextureV(mouseTexture, mousePos, WHITE);//mouse
}

void DrawSettingsPaused() { //?????? non so s sia da mettere qui tbh
	DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(0x000005f));

	//settings body
	DrawRectangle((screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 60, 0, 10, screenHeight / 2, BLACK);//outerborder up2
	DrawRectangle((screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 58, 0, 8, (screenHeight / 2) - 2, RED);//border up2

	DrawRectangle((screenWidth * 0.5) + (MeasureText("Settings", TitleFont) / 2) + 50, screenHeight /2, 10, screenHeight / 2, BLACK);//outerborder down2
	DrawRectangle((screenWidth * 0.5) + (MeasureText("Settings", TitleFont) / 2) + 50, screenHeight /2 + 2, 8,screenHeight / 2 - 2, RED);//border down2ù

	DrawRectangle((screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 50, 0, MeasureText("Settings", TitleFont) + 100, screenHeight, BLACK);//outerbody
	DrawRectangle((screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 45, 0, MeasureText("Settings", TitleFont) + 90, screenHeight, GRAY);//innerbody

  //button
	DrawSettings(sys.setting);

  //separator line
	DrawLineEx((Vector2) { (screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 37, 198 }, (Vector2) { (screenWidth * 0.5) + (MeasureText("Settings", TitleFont) / 2) + 33, 198 }, 3, BLACK);
	DrawLineEx((Vector2) { (screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 35, 200 }, (Vector2) { (screenWidth * 0.5) + (MeasureText("Settings", TitleFont) / 2) + 35, 200 }, 3, RED);
	DrawLineEx((Vector2) { (screenWidth * 0.5) - (MeasureText("Settings", TitleFont) / 2) - 33, 202 }, (Vector2) { (screenWidth * 0.5) + (MeasureText("Settings", TitleFont) / 2) + 37, 202 }, 3, BLACK);
}
 */
