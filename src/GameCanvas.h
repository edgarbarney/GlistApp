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

private:
	static const int KEY_A, KEY_D, KEY_S, KEY_W;

	static const int characterframenum = 6, enemyframenum = 8;
	static const int enemynum = 20;

	gImage background; //Arkaplanimizi tanimladik
	gImage levelmap;
	gImage character[characterframenum]; // Karakterimizi tanimladik
	gImage enemyimage[enemyframenum];
	gImage mapcharactersign, mapenemysign;
	float crot;
	int cx, cy, cw, ch;
	int ccdx, ccdy;
	float cspeed;
	float cdx, cdy;
	int characterframeno;
	int characterframecounter, characterframecounterlimit;
	int keyno, keystate;
	void moveCharacter();
	void moveCamera();
	void moveEnemies();
	void drawBackground();
	void drawEnemies();
	void drawCharacter();
	void drawLevelMap();
	void drawGui();
	gRect bgsrc, bgdst;
	int cammarginleft, cammarginright, cammargintop, cammarginbottom;
	int camx, camy, camw, camh;
	Enemy enemy[enemynum];
	int enemyw, enemyh;
	int mapx, mapy;
	float enemydx, enemydy;
};

#endif /* GAMECANVAS_H_ */
