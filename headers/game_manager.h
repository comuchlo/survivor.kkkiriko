#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
//#include <pthread.h>

// general structs -----------
typedef struct {
  int choice;
  int volume[3];
  bool pause;
  int setting;
} System;
//---------------------------

typedef enum {
  IDLE,
  RUNNING_RIGHT,
  RUNNING_LEFT,
  THROWING_KUNAI
} PlayerActions;

typedef struct {
  float x, y;
  int width, height, vita;
  double xVel, yVel;
  bool hitten;
  unsigned short int hittenFrame, runningFrame, throwingFrame;
  unsigned long long score;
  PlayerActions action;
  //Rectangle oldRec;
  Texture2D texture, attackTexture, kunaiTexture;
} Player;

typedef enum {
  CIAMBELLA,
  CIAMBELLACHAD,
  CIAMBELLAKING
} TypeEnemy;

typedef struct {
  float x, y;
  int width, height;
  int vita;
  double xVel, yVel;
  bool hitted;
  unsigned short frameHit;
  Rectangle oldRec;
  TypeEnemy typeEnemy;
  Texture2D texture;
} Enemy;

typedef struct {
  float x, y;
  double xVel, yVel;
  double nearest;
  int nearestIndex;
} Kunai;

// region:    --- Vector Of Enemies

typedef struct {
  Enemy *data;
  int size;
  int capacity;
} VectorEnemies;

/*typedef struct {
  char verso;
  int i;
} ArgomentiCollisione;*/

VectorEnemies *createVectorEnemies(unsigned int length) {
  VectorEnemies *vec = (VectorEnemies *) malloc(sizeof(VectorEnemies));

  vec->size = 0;
  vec->capacity = length;
  vec->data = (Enemy *) malloc(vec->capacity * sizeof(Enemy));

  return vec;
}

Enemy vectorPopIndexEnemies(VectorEnemies *vec, int index) {
  if (index >= vec->capacity) printf("L'index e' fuori i limiti -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  Enemy returnValue = vec->data[index];

  for (int i = index; i < vec->size - 1; i++)
    vec->data[i] = vec->data[i + 1];

  vec->size -= 1;

  return returnValue;
}

Enemy vectorPopEnemies(VectorEnemies *vec) {
  Enemy returnValue = vec->data[--vec->size];

  return returnValue;
}

Enemy vectorGetEnemies(VectorEnemies *vec, int index) {
  if (index >= vec->capacity) printf("L'index supera il numero di capacita' -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  return vec->data[index];
}

void vectorSetEnemies(VectorEnemies *vec, int index, Enemy value) {
  if (index >= vec->capacity) {
    vec->capacity += 1;

    vec->data = (Enemy *) realloc(vec->data, vec->capacity * sizeof(Enemy));
  }

  vec->size += 1;

  vec->data[index] = value;
}

void vectorPushEnemies(VectorEnemies *vec, Enemy value) {
  if (vec->size == vec->capacity) {
    vec->capacity += 1;

    vec->data = (Enemy *) realloc(vec->data, vec->capacity * sizeof(Enemy));
  }

  vec->data[vec->size] = value;
  vec->size += 1;
}

void vectorReserveEnemies(VectorEnemies *vec, int new_capacity) {
  if (vec->capacity >= new_capacity) printf("L'index supera il numero di capacita' -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  vec->capacity = new_capacity;
  vec->data = (Enemy *) realloc(vec->data, vec->capacity * sizeof(Enemy));
}

void vectorResizeEnemies(VectorEnemies *vec, int length) {
  vec->capacity = length;
  vec->data = (Enemy *) realloc(vec->data, vec->capacity * sizeof(Enemy));
}

void vectorShrinkEnemies(VectorEnemies *vec) {
  vec->capacity = vec->size;
  vec->data = (Enemy *) realloc(vec->data, vec->capacity * sizeof(Enemy));
}

void vectorClearEnemies(VectorEnemies *vec) {
  vec->size = 0;
  vec->capacity = 0;

  vec->data = (Enemy *) realloc(vec->data, 0);
}

void vectorEnemiesSetX(VectorEnemies *vec, float x, int index) {
  vec->data[index].x = x;
}

void vectorEnemiesSetY(VectorEnemies *vec, float y, int index) {
  vec->data[index].y = y;
}

void vectorEnemiesSetWidth(VectorEnemies *vec, int width, int index) {
  vec->data[index].width = width;
}

void vectorEnemiesSetHeight(VectorEnemies *vec, int height, int index) {
  vec->data[index].height = height;
}

void vectorEnemiesSetVita(VectorEnemies *vec, int vita, int index) {
  vec->data[index].vita = vita;
}

void vectorEnemiesSetXVel(VectorEnemies *vec, double xVel, int index) {
  vec->data[index].xVel = xVel;
}

void vectorEnemiesSetYVel(VectorEnemies *vec, double yVel, int index) {
  vec->data[index].yVel = yVel;
}

void vectorEnemiesSetHitted(VectorEnemies *vec, bool hitted, int index) {
  vec->data[index].hitted = hitted;
}

void vectorEnemiesSetFrameHit(VectorEnemies *vec, unsigned short frameHit, int index) {
  vec->data[index].frameHit = frameHit;
}

void vectorEnemiesSetTypeEnemy(VectorEnemies *vec, TypeEnemy typeEnemy, int index) {
  vec->data[index].typeEnemy = typeEnemy;
}

void vectorEnemiesSetTexture(VectorEnemies *vec, Texture2D texture, int index) {
  vec->data[index].texture = texture;
}

/*void vectorEnemiesSetOldRec(VectorEnemies *vec, Rectangle oldRec, int index) {
  vec->data[index].oldRec = oldRec;
}*/

void vectorDeleteEnemies(VectorEnemies *vec) {
  free(vec->data);
  free(vec);
}

// endregion: --- Vector Of Enemies

// region:    --- Vector Of Kunai

typedef struct {
  Kunai *data;
  int size;
  int capacity;
} VectorKunais;

VectorKunais *createVectorKunais(unsigned int length) {
  VectorKunais *vec = (VectorKunais *) malloc(sizeof(VectorKunais));

  vec->size = 0;
  vec->capacity = length;
  vec->data = (Kunai *) malloc(vec->capacity * sizeof(Kunai));

  return vec;
}

Kunai vectorPopIndexKunais(VectorKunais *vec, int index) {
  if (index >= vec->capacity) printf("L'index e' fuori i limiti -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  Kunai returnValue = vec->data[index];

  for (int i = index; i < vec->size - 1; i++)
    vec->data[i] = vec->data[i + 1];

  vec->size -= 1;

  return returnValue;
}

Kunai vectorPopKunais(VectorKunais *vec) {
  Kunai returnValue = vec->data[--vec->size];

  return returnValue;
}

Kunai vectorGetKunais(VectorKunais *vec, int index) {
  if (index >= vec->capacity) printf("L'index supera il numero di capacita' -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  return vec->data[index];
}

void vectorSetKunais(VectorKunais *vec, int index, Kunai value) {
  if (index >= vec->capacity) {
    vec->capacity += 1;

    vec->data = (Kunai *) realloc(vec->data, vec->capacity * sizeof(Kunai));
  }

  vec->size += 1;

  vec->data[index] = value;
}

void vectorPushKunais(VectorKunais *vec, Kunai value) {
  if (vec->size == vec->capacity) {
    vec->capacity += 1;

    vec->data = (Kunai *) realloc(vec->data, vec->capacity * sizeof(Kunai));
  }

  vec->data[vec->size] = value;
  vec->size += 1;
}

void vectorReserveKunais(VectorKunais *vec, int new_capacity) {
  if (vec->capacity >= new_capacity) printf("L'index supera il numero di capacita' -- LINEA[%d], FILE[%s] --\n", __LINE__, __FILE__);

  vec->capacity = new_capacity;
  vec->data = (Kunai *) realloc(vec->data, vec->capacity * sizeof(Kunai));
}

void vectorResizeKunais(VectorKunais *vec, int length) {
  vec->capacity = length;
  vec->data = (Kunai *) realloc(vec->data, vec->capacity * sizeof(Kunai));
}

void vectorShrinkKunais(VectorKunais *vec) {
  vec->capacity = vec->size;
  vec->data = (Kunai *) realloc(vec->data, vec->capacity * sizeof(Kunai));
}

void vectorClearKunais(VectorKunais *vec) {
  vec->size = 0;
  vec->capacity = 0;

  vec->data = (Kunai *) realloc(vec->data, 0);
}

void vectorKunaisSetX(VectorKunais *vec, float x, int index) {
  vec->data[index].x = x;
}

void vectorKunaisSetY(VectorKunais *vec, float y, int index) {
  vec->data[index].y = y;
}

void vectorKunaisSetXVel(VectorKunais *vec, double xVel, int index) {
  vec->data[index].xVel = xVel;
}

void vectorKunaisSetYVel(VectorKunais *vec, double yVel, int index) {
  vec->data[index].yVel = yVel;
}

void vectorKunaisSetNearest(VectorKunais *vec, double nearest, int index) {
  vec->data[index].nearest = nearest;
}

void vectorKunaisSetNearestIndex(VectorKunais *vec, int nearestIndex, int index) {
  vec->data[index].nearestIndex = nearestIndex;
}

void vectorDeleteKunais(VectorKunais *vec) {
  free(vec->data);
  free(vec);
}

// endregion: --- Vector Of Kunai

double pitagora(Vector2 vettore) {
  return sqrt(pow((double) vettore.x, 2) + pow((double) vettore.y, 2));
}

Vector2 normalizeVector(Vector2 vettore) {
  double ipotenusa = pitagora(vettore);

  if (ipotenusa > 0) {
    return (Vector2) { (float) vettore.x / ipotenusa, (float) vettore.y / ipotenusa };
  } else {
    return (Vector2) { (float) 0, (float) 0 };
  }
}

// global variables ---------
 int screenWidth, screenHeight;
const short int playerSpeed = 250, enemySpeed = 250, kunaiSpeed = 500, kunaiDamage = 40;
const short int offsetMappe = 50, frameAnimazioneCamminata = 8, fpsAnimazioneCamminata = 8;
const short int kunaiSize = 32, map2Width = 15360, map2Height = 8640, rangeSpawnEnemies = 1000;
const short int ciambellaSize = 22, ciambellaChadWidth = 128, ciambellaChadHeight = 172, ciambellaKingSize = 128;
unsigned long long bestSurvivedTime, bestScore;
float eSpeedMultiplier = 1, pSpeedMultiplier = 1;
Vector2 mousePos;
Player player1, player2;
System sys;
VectorEnemies *enemies1, *enemies2;
VectorKunais *kunais1, *kunais2;
Rectangle actualScreen, resumeBtn, trainingOptBtn, settingsBtn, exitBtn, tryAgainBtn, playAgainBtn, gotoLobbyBtn;
Camera2D camera1, camera2;
Texture2D lobbyBg, map1, map2, trainingFloor, mouseTexture, ciambellaTexture, ciambellaChadTexture, ciambellaKingTexture;
Sound slash, currentSound;
Music lobbyMusic, survivalMusic, duelMusic, currentMusic;
RenderTexture2D idealScreen, renderTexture1, renderTexture2;
//--------------------------

/* ------------ ----------------------------- Lobby & Settings section --------------------------------------*/
// general defines ------
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

#define TitleFont 90
#define subTitleFont 60
#define buttonFont 40
#define textFont 30
#define lobbyOpt 7
#define settingsOpt 4
//-----------------------

void DrawTextSF(const char *text, int x, int y, int font, Color col1, Color col2, Color col3) {
	DrawText(text, x - 2, y - 2, font, col1);
	DrawText(text, x, y, font, col2);
	DrawText(text, x + 2, y + 2, font, col3);
}

void DrawRangeBar(int progress, int height) {
	int progressLenght = (!progress) ? 0 : progress * 2.5;

	DrawRectangle((screenWidth / 2) - 127, height, 10, 19, GetColor(0x232323ff));//first end of bar
	DrawRectangle((screenWidth / 2) + 117, height + 5, 10, 19, GetColor(0x232323ff));//end of bar
	DrawRectangle((screenWidth / 2) - 127, height + 5, 254, 14, GetColor(0x232323ff));//outerBar
	DrawRectangle((screenWidth / 2) - 125, height + 7, 250, 10, WHITE);//innerBar
	DrawRectangle((screenWidth / 2) - 125, height + 7, progressLenght, 10, RED);//Master Volume Level

	DrawText(TextFormat("%d", progress), (screenWidth / 2) + 136, height + 2, 18, BLACK);//Master Volume Number
	DrawText(TextFormat("%d", progress), (screenWidth / 2) + 137, height + 3, 18, BLACK);//Master Volume Number
	DrawText(TextFormat("%d", progress), (screenWidth / 2) + 138, height + 4, 18, RED);//Master Volume Number

	DrawRectangle((screenWidth / 2) - 127 + progressLenght, height - 1, 10, 26, BLACK);//outerRangeCursor
	DrawRectangle((screenWidth / 2) - 125 + progressLenght, height + 1, 6, 22, RED);//innerRangeCursor
}

void DrawArrowSF(int x, int y, int width, int height, int thick, bool verse, Color col1, Color col2, Color col3) {
	if (!verse)  {
		DrawLineEx((Vector2){x-2,y-2},(Vector2){x+width-2,y+(height/2)-2},thick,col1);
		DrawLineEx((Vector2){x-2,y+height-2},(Vector2){x+width-2,y+(height/2)-2},thick,col1);

		DrawLineEx((Vector2){x,y},(Vector2){x+width,y+(height/2)},thick,col2);
		DrawLineEx((Vector2){x,y+height},(Vector2){x+width,y+(height/2)},thick,col2);

		DrawLineEx((Vector2){x+2,y+2},(Vector2){x+width+2,y+(height/2)+2},thick,col3);
		DrawLineEx((Vector2){x+2,y+height+2},(Vector2){x+width+2,y+(height/2)+2},thick,col3);
	} else {
		DrawLineEx((Vector2){x+width-2,y-2},(Vector2){x-2,y+(height/2)-2},thick,col1);
		DrawLineEx((Vector2){x+width-2,y+height-2},(Vector2){x-2,y+(height/2)-2},thick,col1);

		DrawLineEx((Vector2){x+width,y},(Vector2){x,y+(height/2)},thick,col2);
		DrawLineEx((Vector2){x+width,y+height},(Vector2){x,y+(height/2)},thick,col2);

		DrawLineEx((Vector2){x+width+2,y+2},(Vector2){x+2,y+(height/2)+2},thick,col3);
		DrawLineEx((Vector2){x+width+2,y+height+2},(Vector2){x+2,y+(height/2)+2},thick,col3);
	}
}

void DrawLobby(int choice) { //: training , duel , survival , settings
  ClearBackground(BLACK);

  // title
  DrawTextSF("Kiriko", (screenWidth / 2) - (MeasureText("Kiriko", TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);
	DrawTextSF("and the donuts", (screenWidth / 2) - (MeasureText("and the donuts", subTitleFont) / 2) + 2, 142, subTitleFont, RED, BLACK, BLACK);

	//training
	DrawTextSF("Training", 12, 252, buttonFont, BLACK, BLACK, (sys.choice == 1) ? RED : WHITE);

	//duel
	DrawTextSF("Duel", 12, 302, buttonFont, BLACK, BLACK, (sys.choice == 2) ? RED : WHITE);

	//survival
	DrawTextSF("Survival", 12, 352, buttonFont, BLACK, BLACK, (sys.choice == 3) ? RED : WHITE);

	//settings
	DrawTextSF("Settings", 12, 402, buttonFont, BLACK, BLACK, (sys.choice == 4) ? RED : WHITE);

	//how to play
	DrawTextSF("How to play", 12, 452, buttonFont, BLACK, BLACK, (sys.choice == 5) ? RED : WHITE);

	//credits
	DrawTextSF("Credits", 12, 502, buttonFont, BLACK, BLACK, (sys.choice == 6) ? RED : WHITE);

	//exit game
	DrawTextSF("Exit game", 12, 552, buttonFont, BLACK, BLACK, (sys.choice == 7) ? RED : WHITE);
}

void DrawTrainingSettings() {
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

void DrawSettings(int choice) { //: master volume , music volume , effects volume
  // title
  DrawTextSF("Settings", (screenWidth / 2) - (MeasureText("Settings", TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);

  //Master Volume
	DrawTextSF("Master Volume", (screenWidth / 2) - (MeasureText("Master Volume", buttonFont) / 2), 250, buttonFont, BLACK, BLACK, (choice == 40) ? RED : WHITE);

	int shiftDown = 0, volumeLevel;//shift down all below if smth is focussed & lvl in px of certain volume

	if (choice == 40) {//Master Volume range bar if MasterVolume is focussed
		shiftDown = 60;
    DrawRangeBar(sys.volume[0], 303);
	}

	//Music Volume
	DrawTextSF("Music Volume", (screenWidth / 2) - (MeasureText("Music Volume", buttonFont) / 2), 310 + shiftDown, buttonFont, BLACK, BLACK, (choice == 41) ? RED : WHITE);

	if (choice == 41) {//Music Volume range bar if MusicVolume is focussed
		shiftDown = 60;
		DrawRangeBar(sys.volume[1], 363);
	}

	//Effects Volume
	DrawTextSF("Effects Volume", (screenWidth / 2) - (MeasureText("Effects Volume", buttonFont) / 2), 370 + shiftDown, buttonFont, BLACK, BLACK, (choice == 42) ? RED : WHITE);

	if (choice == 42) {//Effects Volume range bar if EffectsVolume is focussed
		shiftDown = 60;
		DrawRangeBar(sys.volume[2], 423);
	}

	//reset the settings
	DrawTextSF("Reset the Settings", (screenWidth / 2) - (MeasureText("Reset the Settings", buttonFont) / 2), 430 + shiftDown, buttonFont, BLACK, BLACK, (choice == 43) ? RED : WHITE);
	//Exit
	DrawTextSF("Exit", ( screenWidth / 2) - (MeasureText("Exit", buttonFont) / 2), 490 + shiftDown, buttonFont, BLACK, BLACK, (choice == 40 + settingsOpt) ? RED : WHITE);
}

void HandleSettingsEvents(int *choice, int pause) {
	//events
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {//up
		*choice -= 1;
		if (*choice < 40) *choice = 40 + settingsOpt;
		PlaySound(currentSound);
	}

	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {//down
		*choice += 1;
		if (*choice > 40 + settingsOpt) *choice = 40;
		PlaySound(currentSound);
	}

	if  ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && *choice < 40 + settingsOpt) {//right
		sys.volume[*choice - 40] = (sys.volume[*choice - 40] + 5 > 100) ? 100 : sys.volume[*choice - 40] + 5;//prevent overpass 100

		if (*choice == 40 || *choice == 41) {
			SetMusicVolume(currentMusic, ((float) sys.volume[1] / 100) * ((float) sys.volume[0] / 100));//adapt new volume
		}

		if (*choice == 40 || *choice == 42) {
			SetSoundVolume(currentSound, ((float) sys.volume[2] / 100) * ((float) sys.volume[0] / 100));//adapt new volume
		}
	}

	if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && *choice < 40 + settingsOpt) {//left
		sys.volume[*choice - 40] = (sys.volume[*choice - 40] - 5 < 0) ? 0 : sys.volume[*choice - 40] - 5;//prevent overpass 0

		if (*choice == 40 || *choice == 41) {
			SetMusicVolume(currentMusic, ((float) sys.volume[1] / 100) * ((float) sys.volume[0] / 100));//adapt new volume
		}

		if (*choice == 40 || *choice == 42) {
			SetSoundVolume(currentSound, ((float) sys.volume[2] / 100) * ((float) sys.volume[0] / 100));//adapt new volume
		}
	}

	if (IsKeyPressed(KEY_ENTER))  {//enter
		if (*choice == 43) {//reset settings
			sys.volume[0] = 75;
			sys.volume[1] = 50;
			sys.volume[2] = 70;
			SetMusicVolume(currentMusic, ((float) sys.volume[1] / 100) * ((float) sys.volume[0] / 100));
			SetSoundVolume(currentSound, ((float) sys.volume[2] / 100) * ((float) sys.volume[0] / 100));
		} else if (*choice == 40 + settingsOpt) {//exit
			*choice = pause;//back to prew/paused choice
		}
	}
}

/* ---------------------------------------------------------------------------------------------------------*/

void DrawPause() {
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

void DrawSettingsPaused() {
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

void InitTraining() {
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

void InitDuel() {
  player1.x = screenWidth / 4 - 100;
  player1.y = screenHeight / 2 - 100;
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
  /*player1.oldRec = (Rectangle) {
    player1.x,
    player1.y,
    player1.width,
    player1.height
  };*/

  player2.x = screenWidth / 4 - 100;
  player2.y = screenHeight / 2 - 100;
  player2.width = 200;
  player2.height = 200;
  player2.vita = 100;
  player2.hitten = false;
  player2.hittenFrame = 0;
  player2.runningFrame = 0;
  player2.throwingFrame = 0;
  player2.score = 0;
  player2.action = IDLE;
  player2.xVel = playerSpeed;
  player2.yVel = playerSpeed;
  /*player2.oldRec = (Rectangle) {
    player2.x,
    player2.y,
    player2.width,
    player2.height
  };*/

  int randomEnemyX, randomEnemyY;
  Enemy enemy;

  vectorClearEnemies(enemies1);
  vectorResizeEnemies(enemies1, 10);

  for (int i = 0; i < enemies1->capacity; i++) {
    do {
      randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x);

    do {
      randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y);

    enemy.x = randomEnemyX;
    enemy.y = randomEnemyY;
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

    vectorSetEnemies(enemies1, i, enemy);
  }

  vectorClearEnemies(enemies2);
  vectorResizeEnemies(enemies2, 10);

  for (int i = 0; i < enemies2->capacity; i++) {
    do {
      randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x);

    do {
      randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y);

    enemy.x = randomEnemyX;
    enemy.y = randomEnemyY;
    enemy.typeEnemy = CIAMBELLA;
    enemy.width = ciambellaSize * 3;
    enemy.height = ciambellaSize * 3;
    enemy.vita = 75;
    enemy.frameHit = 0;

    Vector2 vettoreVelocitaNemico = normalizeVector(
      (Vector2) {
        player2.x + player2.width / 2 - enemy.x + enemy.width / 2,
        player2.y + player2.height / 2 - enemy.y + enemy.height / 2
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

    vectorSetEnemies(enemies2, i, enemy);
  }

  vectorClearKunais(kunais1);
  vectorClearKunais(kunais2);
}

void DrawDuel() {
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

void InitSurvival() {
  player1.x = screenWidth / 2 - 100;
  player1.y = screenHeight / 2 - 100;
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
  /*player1.oldRec = (Rectangle) {
    player1.x,
    player1.y,
    player1.width,
    player1.height
  };*/

  int randomEnemyX, randomEnemyY;
  Enemy enemy;

  vectorClearEnemies(enemies1);
  vectorResizeEnemies(enemies1, 50);

  for (int i = 0; i < 10; i++) {
    do {
      randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x + player1.width);

    do {
      randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y + player1.height);

    enemy.x = randomEnemyX;
    enemy.y = randomEnemyY;
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
  }

  vectorClearKunais(kunais1);
}

void DrawSurvival() {
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

void SpawnNewEnemies(VectorEnemies *enemies) {
  int randomEnemyX, randomEnemyY;
  unsigned short int randomEnemyType;
  Enemy enemy;

  for (int i = 0; i < 10; i++) {
    do {
      randomEnemyX = rand() % ((int) player1.x + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.x - rangeSpawnEnemies / 2 <= randomEnemyX && randomEnemyX <= rangeSpawnEnemies / 2 + player1.x);

    do {
      randomEnemyY = rand() % ((int) player1.y + rangeSpawnEnemies * 2) - rangeSpawnEnemies + 1;
    } while (player1.y - rangeSpawnEnemies / 2 <= randomEnemyY && randomEnemyY <= rangeSpawnEnemies / 2 + player1.y);

    enemy.x = randomEnemyX;
    enemy.y = randomEnemyY;

    randomEnemyType = rand() % 12 + 1;

    if (randomEnemyType >= 1 && randomEnemyType <= 6) {
      enemy.typeEnemy = CIAMBELLA;
      enemy.width = ciambellaSize * 3;
      enemy.height = ciambellaSize * 3;
      enemy.vita = 75;
    } else if (randomEnemyType > 6  && randomEnemyType <= 10) {
      enemy.typeEnemy = CIAMBELLACHAD;
      enemy.width = ciambellaChadWidth;
      enemy.height = ciambellaChadHeight;
      enemy.vita = 225;
    } else {
      enemy.typeEnemy = CIAMBELLAKING;
      enemy.width = ciambellaKingSize;
      enemy.height = ciambellaKingSize;
      enemy.vita = 450;
    }

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

    vectorPushEnemies(enemies, enemy);
  }
}

/*void *checkCollisionsEnemies(void *argomenti) {
  ArgomentiCollisione *argomentiCollisione = (ArgomentiCollisione *) argomenti;
  char verso = argomentiCollisione->verso;
  int i = argomentiCollisione->i;

  Enemy enemy1 = vectorGetEnemies(enemies1, i);

  for (int j = 0; j < enemies1->size; j++) {
    if (j == i)
      continue;

    Enemy enemy2 = vectorGetEnemies(enemies1, j);

    if (CheckCollisionRecs(
      (Rectangle) {
        enemy1.x,
        enemy1.y,
        enemy1.width,
        enemy1.height,
      },
      (Rectangle) {
        enemy2.x,
        enemy2.y,
        enemy2.width,
        enemy2.height,
      }
    )) {
      if (verso == 'o') { // collisione orrizontale
        if (enemy1.x + enemy1.width > enemy2.x && enemy1.oldRec.x + enemy1.oldRec.width < enemy2.oldRec.x) {
          vectorEnemiesSetX(enemies1, -enemy1.width + enemy2.x, i);
        } else if (enemy1.x < enemy2.x + enemy2.width && enemy1.oldRec.x > enemy2.oldRec.x + enemy2.oldRec.width) {
          vectorEnemiesSetX(enemies1, enemy2.x + enemy2.width, i);
        }
      } else if (verso == 'v') { // collisione verticale
        if (enemy1.y + enemy1.height > enemy2.y && enemy1.oldRec.y + enemy1.oldRec.height < enemy2.oldRec.y) {
          vectorEnemiesSetY(enemies1, -enemy1.height + enemy2.y, i);
        } else if (enemy1.y < enemy2.y + enemy2.height && enemy1.oldRec.y > enemy2.oldRec.y + enemy2.oldRec.height) {
          vectorEnemiesSetY(enemies1, enemy2.y + enemy2.height, i);
        }
      }
    }
  }
}*/

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

void DrawEndScore(unsigned long long totalTime) {
	DrawRectangle(0,0,screenWidth,screenHeight,GetColor(0x5e5e5e5f));//darken bg
	//lost/win message
  const char *result;

	if (/*score > sys.highscore &&*/ totalTime > bestSurvivedTime) result = "New Record!";
	/*else if (score > sys.highscore || totalTime > bestSurvivedTime) result = (score>sys.highscore) ? "New High Score!" : "New Best Time!";*/
	else result = "You can do better...";

	DrawTextSF(result, (screenWidth / 2) - (MeasureText(result, TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);
	//highscore
	DrawTextSF(TextFormat("High Score: %llu", bestScore), (screenWidth / 2) - (MeasureText(TextFormat("High Score: %llu", bestScore), subTitleFont) / 2), 250, subTitleFont, RED, BLACK, BLACK);
	//score
	DrawTextSF(TextFormat("Your score: %llu", player1.score), (screenWidth / 2) - (MeasureText(TextFormat("Your score: %llu", player1.score), subTitleFont) / 2), 320, subTitleFont, BLACK, BLACK, (player1.score > bestScore) ? RED : WHITE);
	//best time
	DrawTextSF(TextFormat("Best time: %02llu:%02llu", bestSurvivedTime / 60, bestSurvivedTime % 60), (screenWidth/2)-(MeasureText(TextFormat("Best time: %02d:%02d", floor(bestSurvivedTime / 60), bestSurvivedTime % 60), subTitleFont) / 2), 420, subTitleFont, RED, BLACK, BLACK);
	//time
	DrawTextSF(TextFormat("Your time: %02llu:%02llu", totalTime / 60, totalTime % 60),(screenWidth/2)-(MeasureText(TextFormat("Your time: %02d:%02d", floor(totalTime / 60), totalTime % 60), subTitleFont) / 2), 490, subTitleFont, BLACK, BLACK, (totalTime > bestSurvivedTime) ? RED : WHITE);

	//buttons
	//try again button
	DrawTextSF("Try Again",tryAgainBtn.x,tryAgainBtn.y,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,tryAgainBtn)?RED:WHITE);
	//exit button
	DrawTextSF("Go to Lobby",gotoLobbyBtn.x,gotoLobbyBtn.y,buttonFont,BLACK,BLACK,CheckCollisionPointRec(mousePos,gotoLobbyBtn)?RED:WHITE);

	//mouse
	DrawTextureV(mouseTexture,(Vector2){mousePos.x-19,mousePos.y-19},WHITE);
}

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
}
/* ---------------------------------------------------------------------------------------------------------*/

/* ------------------------------------------------ Credits -------------------------------------------------*/
void DrawCredits() {
	DrawTextureEx(lobbyBg, (Vector2) { 0, 0 }, 0.0f, (float) screenWidth / 1920, WHITE);//bg
	DrawRectangle(0, 0, screenWidth, screenHeight, GetColor(0x5e5e5e5f));//darken bg

	BeginMode2D(camera1);

		DrawTextSF("Credits", (screenWidth * 0.5) - (MeasureText("Credits", TitleFont) / 2), 50, TitleFont, RED, BLACK, BLACK);
		DrawTextSF("Programmers", (screenWidth / 2) - (MeasureText("Programmers", buttonFont) / 2), 200, buttonFont, RED, BLACK, BLACK);
		DrawTextSF("Bardin Gabriele", (screenWidth / 2) - (MeasureText("Bardin Gabriele", buttonFont) / 2), 260, buttonFont, BLACK, BLACK, RED);
		DrawTextSF("Tomas Maceira", (screenWidth / 2) - (MeasureText("Cassandra Maceira", buttonFont) / 2), 310, buttonFont, BLACK, BLACK, RED);

		DrawTextSF("Graphic Designer", (screenWidth / 2) - (MeasureText("Graphic Designer", buttonFont) / 2), 410, buttonFont, RED, BLACK, BLACK);
		DrawTextSF("Textures", (screenWidth / 2) - (MeasureText("Textures", buttonFont) / 2), 460, buttonFont, RED, BLACK, BLACK);
		DrawTextSF("Aron Capraro", (screenWidth / 2) - (MeasureText("Aron Capraro", buttonFont) / 2), 510, buttonFont, BLACK, BLACK, RED);

		DrawTextSF("Maps & Backgrounds", (screenWidth / 2) - (MeasureText("Maps & Backgrounds", buttonFont) / 2), 610, buttonFont, RED, BLACK, BLACK);
		DrawTextSF("Giacomo Pasqualini", (screenWidth / 2) - (MeasureText("Giacomo Pasqualini", buttonFont) / 2), 660, buttonFont, BLACK, BLACK, RED);

		DrawTextSF("Musics produced by", (screenWidth / 2) - (MeasureText("Musics produced by", buttonFont) / 2), 760, buttonFont, RED, BLACK, BLACK);
		DrawTextSF("Marllon Silva / xDeviruchi", (screenWidth / 2) - (MeasureText("Marllon Silva / xDeviruchi", buttonFont) / 2), 820, buttonFont, BLACK, BLACK, RED);

		DrawTextSF("Sounds", (screenWidth / 2) - (MeasureText("Sounds", buttonFont) / 2), 920, buttonFont, RED, BLACK, BLACK);
		DrawTextSF("Giacomo Pasqualini", (screenWidth / 2) - (MeasureText("Giacomo Pasqualini", buttonFont) / 2), 970, buttonFont, BLACK, BLACK, RED);

		DrawTextSF("Thanks for Playing!", (screenWidth / 2) - (MeasureText("Thanks for Playing!", TitleFont) / 2), 1100, TitleFont, RED, BLACK, BLACK);

  EndMode2D();
}
