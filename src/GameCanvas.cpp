/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */


#include "GameCanvas.h"

const int GameCanvas::KEY_A = 2;
const int GameCanvas::KEY_D = 4;
const int GameCanvas::KEY_W = 8;
const int GameCanvas::KEY_S = 16;


GameCanvas::GameCanvas(gBaseApp *root) : gBaseCanvas(root) {
}

GameCanvas::~GameCanvas() {
}

void GameCanvas::setup() {
//	logi("GlistApp setup")
	background.loadImage("oyun/arkaplan1.jpg");
	character.loadImage("oyun/erkek_tufek_00.png");
	for(int i = 0; i < gamepadNum; i++) {
		gamepad[i].loadImage("oyun/gamepad" + gToStr(i) + ".png");
	}
	gpx[0] = gamepad[0].getWidth() / 2;
	gpy[0] = getHeight() - (gamepad[0].getHeight() / 2) - gamepad[0].getHeight();
	gpx[1] = getWidth() - (gamepad[1].getWidth() / 2) - gamepad[1].getWidth();
	gpy[1] = getHeight() - (gamepad[0].getHeight() / 2) - gamepad[0].getHeight();
	crot = 0.0f;
	cx = (getWidth() / 2) - (character.getWidth() / 2);
	cy = (getHeight() / 2) - (character.getHeight() / 2);
	cw = character.getWidth();
	ch = character.getHeight();
	cspeed = 4.0f;
	cdx = 0.0f;
	cdy = 0.0f;
	keystate = 0;
}

	//Coding Covnentions

void GameCanvas::update() {
	//logi("GlistApp update");
	moveCharacter();
}

void GameCanvas::draw() {
	//logi("GlistApp draw");
	//bgsrc.set(0, 0, getWidth(), getHeight());
	//bgdst.set(0, 0, getWidth(), getHeight());
	//background.drawSub(bgsrc, bgdst);
	logi("screenw:" + gToStr(getWidth()) + ", screenh:" + gToStr(getHeight()));
	background.drawSub(0, 0, 1280, 720, 0, 0, getWidth(), getHeight());
	character.draw(cx, cy, cw, ch, crot);
	for(int i = 0; i < gamepadNum; i++) gamepad[i].draw(gpx[i], gpy[i]);
}

/**
 * Karakteri hareket ettiren fonksiyondur. Kullanicinin bastigi tuslari okuyarak karakteri buna gore
 * bir yone dogru hareket ettirme islemini yapar.
 */
void GameCanvas::moveCharacter() {
	if ((keystate & KEY_A) != 0) { // Sagdan ikinci bitte kayit olup olmadigini test ediyoruz
		cdx += -std::cos(gDegToRad(crot)) * cspeed;
		cdy += -std::sin(gDegToRad(crot)) * cspeed;
	} else if ((keystate & KEY_D) != 0) { // Sagdan ucuncu bitte kayit olup olmadigini test ediyoruz
		cdx += std::cos(gDegToRad(crot)) * cspeed;
		cdy += std::sin(gDegToRad(crot)) * cspeed;
	}

	if ((keystate & KEY_W) != 0) { // Sagdan dorduncu bitte kayit olup olmadigini test ediyoruz
		cdx += std::sin(gDegToRad(crot)) * cspeed;
		cdy += -std::cos(gDegToRad(crot)) * cspeed;
	} else if ((keystate & KEY_S) != 0) { // Sagdan besinci bitte kayit olup olmadigini test ediyoruz
		cdx += -std::sin(gDegToRad(crot)) * cspeed;
		cdy += std::cos(gDegToRad(crot)) * cspeed;
	}
	cx += cdx;
	cy += cdy;
	cdx = 0.0f;
	cdy = 0.0f;
}

void GameCanvas::keyPressed(int key) {
	logi("GC", "keyPressed:" + gToStr(key));
	keyno = -1;
	switch(key) {
	case 65: // Key A
		keyno = KEY_A; // Sagdan ikinci bite kayit yapiyoruz
		break;
	case 68: // Key D
		keyno = KEY_D; // Sagdan ucuncu bite kayit yapiyoruz
		break;
	case 87: // Key W
		keyno = KEY_W; // Sagdan dorduncu bite kayit yapiyoruz
		break;
	case 83: // Key S
		keyno = KEY_S; // Sagdan besinci bite kayit yapiyoruz
		break;
	default:
		break;
	}
	if (keyno != -1) keystate |= keyno;
}

void GameCanvas::keyReleased(int key) {
	logi("GC", "keyReleased:" + gToStr(key));
	keyno = -1;
		switch(key) {
		case 65: // Key A
			keyno = KEY_A; // Sagdan ikinci bite kayit yapiyoruz
			break;
		case 68: // Key D
			keyno = KEY_D; // Sagdan ucuncu bite kayit yapiyoruz
			break;
		case 87: // Key W
			keyno = KEY_W; // Sagdan dorduncu bite kayit yapiyoruz
			break;
		case 83: // Key S
			keyno = KEY_S; // Sagdan besinci bite kayit yapiyoruz
			break;
		default:
			break;
		}
		if (keyno != -1) keystate &= ~keyno;
}

void GameCanvas::mouseMoved(int x, int y) {
//	logi("mouseMoved x:" + gToStr(x) + ", y:" + gToStr(y));
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	logi("mouseDragged x:" + gToStr(x) + ", y:" + gToStr(y) + ", b:" + gToStr(button));
	crot = (int)(gRadToDeg((float)std::atan2((float)y - cy, (float)x - cx)) + 90.0f + 360.0f) % 360;
}

void GameCanvas::mousePressed(int x, int y, int button) {
	crot = (int)(gRadToDeg((float)std::atan2((float)y - cy, (float)x - cx)) + 90.0f + 360.0f) % 360;
	//logi("crot : " + gToStr(crot));
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	logi("GC", "mouseReleased, button:" + gToStr(button));
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

// TERMS
// Coding Conventions
// Main Loop
// Synchronized/Asynchronized Functions
// Bitwise Operations
