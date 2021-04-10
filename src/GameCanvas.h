/*
 * GameCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GAMECANVAS_H_
#define GAMECANVAS_H_

#include "gBaseCanvas.h"
#include "gImage.h"
#include "Enemy.h"
#include "gFont.h"


class GameCanvas : public gBaseCanvas {
public:
	GameCanvas(gBaseApp *root);
	virtual ~GameCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered();
	void mouseExited();

	void showNotify();
	void hideNotify();

	void setSelectedCharacterNo(int selectedCharacterNo);

private:
	static const int KEY_A, KEY_D, KEY_S, KEY_W;
	static const int KEYCODE_ESC = 256;
	static const int ENEMYANIMATION_WALK = 0, ENEMYANIMATION_ATTACK = 1, ENEMYANIMATION_DEATH = 2;
	static const int BULLETSENDER_CHARACTER = 0, BULLETSENDER_ENEMY = 1;

	static const int characterframenum = 6, enemyanimationnum = 3, enemymaxframenum = 16, enemyframenum = 8;
	static const int enemynum = 20;

	gImage background; //Arkaplanimizi tanimladik
	gImage levelmap;
	gImage character[characterframenum]; // Karakterimizi tanimladik
	gImage enemyimage[enemyanimationnum][enemymaxframenum];
	gImage mapcharactersign, mapenemysign;
	gImage bullet[2];
	gImage charactericon;
	gImage healthicon;
	gImage healthbarframe;
	gImage healthbarbackground;
	gImage healthbar;
	gImage enemyicon;
	gImage enemybar;
	gImage pausedialogue;
	gImage continuebutton, mainmenubutton;
	gImage gameoverdialogue;
	gImage replaybutton;
	float crot;
	float cx, cy, cw, ch;
	int ccdx, ccdy;
	float cspeed;
	float cdx, cdy;
	int characterframeno;
	int characterframecounter, characterframecounterlimit;
	int keyno, keystate;
	void moveCharacter();
	void moveCamera();
	void moveEnemies();
	void moveBullets();
	void drawBackground();
	void drawEnemies();
	void drawCharacter();
	void drawBullets();
	void drawLevelMap();
	void drawGui();
	void drawDialogue();
	void generateBullet(float bulletx, float bullety, float bulletdx, float bulletdy, float bulletrotation, int bulletSender);
	gRect bgsrc, bgdst;
	int cammarginleft, cammarginright, cammargintop, cammarginbottom;
	int camx, camy, camw, camh;
	int enemyanimationframenum[enemyanimationnum];
	bool enemyanimationloop[enemyanimationnum];
	Enemy enemy[enemynum];
	int enemyw, enemyh;
	int liveenemynum;
	int mapx, mapy;
	float enemydx, enemydy;
	float enemyspeed;
	bool checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2);
	bool enemynear;
	std::vector<std::vector<float>> bullets;
	float bulletspeed;
	int bulletrange;
	int bulletw, bulleth;
	float muzzledistance, muzzledangle, muzzleangle;
	int bsender;
	gFont font;
	float handdistance[2], handdangle[2], handangle[2];
	int chealth;
	int chealthcounter, chealthcounterlimit;
	int charactericonx, charactericony;
	int healthx, healthy;
	int healthbarframex, healthbarframey;
	int healthbarbackgroundx, healthbarbackgroundy;
	int enemyiconx, enemyicony;
	int enemybarx, enemybary;
	int enemybarbackgroundx, enemybarbackgroundy;
	int selectedcharacterno;
	std::string gender;
	int dialoguex, dialoguey, dialoguew, dialogueh;
	int leftbuttonx, leftbuttony, leftbuttonw, leftbuttonh;
	int rightbuttonx, rightbuttony, rightbuttonw, rightbuttonh;
	bool pausedialogueshown;
	bool gameoverdialogueshown;
};

#endif /* GAMECANVAS_H_ */
