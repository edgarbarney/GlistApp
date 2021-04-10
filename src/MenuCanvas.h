/*
 * MenuCanvas.h
 *
 *  Created on: 4 Apr 2021
 *      Author: kiwim
 */

#ifndef SRC_MENUCANVAS_H_
#define SRC_MENUCANVAS_H_

#include "gBaseCanvas.h"
#include "gImage.h"

class MenuCanvas: public gBaseCanvas {
public:
	MenuCanvas(gBaseApp *root);
	virtual ~MenuCanvas();

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
	gImage background;
	gImage mainmenu;
	gImage checkbox;
	gImage muteimage;
	int menux, menuy;
	int playx, playy, playw, playh;
	int cbx[2], cby, cbw, cbh;
	int cimagex[2], cimagey, cimagew, cimageh;
	int selectedcharacter;
	int musicbuttonx, musicbuttony;
	int soundbuttonx, soundbuttony;
	int buttonw, buttonh;
	int musicmutex, musicmutey;
	int soundmutex, soundmutey;
	bool musicon, soundon;
};

#endif /* SRC_MENUCANVAS_H_ */
