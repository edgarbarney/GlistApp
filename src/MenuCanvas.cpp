/*
 * MenuCanvas.cpp
 *
 *  Created on: 4 Apr 2021
 *      Author: kiwim
 */

#include "MenuCanvas.h"
#include "GameCanvas.h"


MenuCanvas::MenuCanvas(gBaseApp *root) : gBaseCanvas(root) {
	// TODO Auto-generated constructor stub

}

MenuCanvas::~MenuCanvas() {
	// TODO Auto-generated destructor stub
}

void MenuCanvas::setup() {
	background.loadImage("menu/arkaplan.jpg");
	mainmenu.loadImage("menu/anamenu.png");
	checkbox.loadImage("menu/tikler.png");
	muteimage.loadImage("menu/ban.png");
	menux = (getWidth() / 2) - (mainmenu.getWidth() / 2);
	menuy = (getHeight() / 2) - (mainmenu.getHeight() / 2);
	playx = menux + 76;
	playy = menuy + 295;
	playw = 140;
	playh = 58;
	for (int i = 0; i < 2; i++) {
		cbx[i] = menux + 386 - (3 * checkbox.getHeight() / 2) + (i * 2 * checkbox.getHeight());
	}
	cby = menuy + 415 - 3 * checkbox.getHeight() / 2;
	cbw = checkbox.getWidth() / 2;
	cbh = checkbox.getHeight();
	for (int i = 0; i < 2; i++) {
		cimagex[i] = (menux + 210) + (i * 177);
	}
	cimagey = menuy + 65;
	cimagew = 175;
	cimageh = 340;
	selectedcharacter = 0;
	musicbuttonx = menux + 98;
	musicbuttony = menuy + 141;
	buttonw = 95;
	buttonh = 25;
	soundbuttonx = menux + 98;
	soundbuttony = menuy + 167;
	musicmutex = musicbuttonx + (buttonw / 2) - muteimage.getWidth() / 2;
	soundmutex = musicmutex;
	musicmutey = musicbuttony + (buttonh / 2) - muteimage.getHeight() / 2;
	soundmutey = soundbuttony + (buttonh / 2) - muteimage.getHeight() / 2;
	musicon = true;
	soundon = true;
}

void MenuCanvas::update() {

}

void MenuCanvas::draw() {
	background.draw(0, 0, getWidth(), getHeight());
	mainmenu.draw(menux, menuy);
	checkbox.drawSub(cbx[0], cby, cbw, cbh, (1 - selectedcharacter) * checkbox.getWidth() / 2, 0, cbw, cbh);
	checkbox.drawSub(cbx[1], cby, cbw, cbh, selectedcharacter * checkbox.getWidth() / 2, 0, cbw, cbh);
	if (!musicon) {
		muteimage.draw(musicmutex, musicmutey);
	}
	if (!soundon) {
		muteimage.draw(soundmutex, soundmutey);
	}
}

void MenuCanvas::keyPressed(int key) {

}

void MenuCanvas::keyReleased(int key) {

}

void MenuCanvas::mouseMoved(int x, int y ) {

}

void MenuCanvas::mouseDragged(int x, int y, int button) {

}

void MenuCanvas::mousePressed(int x, int y, int button) {

}

void MenuCanvas::mouseReleased(int x, int y, int button) {
	if (x >= playx && x < playx + playw && y >= playy && y < playy + playh) {
		GameCanvas *cnv = new GameCanvas(root);
		root->getAppManager()->setCurrentCanvas(cnv);
	}
	if (x >= cimagex[0] && x < cimagex[0] + cimagew && y >= cimagey && y < cimagey + cimageh) {
		selectedcharacter = 0;
	}
	if (x >= cimagex[1] && x < cimagex[1] + cimagew && y >= cimagey && y < cimagey + cimageh) {
		selectedcharacter = 1;
	}
	if (x >= musicbuttonx && x < musicbuttonx + buttonw && y >= musicbuttony && y < musicbuttony + buttonh) {
		musicon = !musicon;
	}
	if (x >= soundbuttonx && x < soundbuttonx + buttonw && y >= soundbuttony && y < soundbuttony + buttonh) {
		soundon = !soundon;
	}

}

void MenuCanvas::mouseEntered() {

}

void MenuCanvas::mouseExited() {

}


void MenuCanvas::showNotify() {

}

void MenuCanvas::hideNotify() {

}
