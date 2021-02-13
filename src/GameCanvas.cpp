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

/**
 * Oyunda kullanilan tum degiskenlerin ilk degerleri burada verilir.
 */
void GameCanvas::setup() {
//	logi("GlistApp setup");
	background.loadImage("oyun/arkaplan1.jpg"); // Arkaplan resmini ekledik
	for (int i = 0; i < characterframenum; i++) character[i].loadImage("oyun/erkek_tufek_0" + gToStr(i) + ".png"); // Karakterimizi ekledik
	crot = 0.0f;
	cx = (getWidth() - character[0].getWidth()) >> 1;
	cy = (getHeight() - character[0].getHeight()) >> 1;
	cw = character[0].getWidth();
	ch = character[0].getHeight();
	cspeed = 4.0f;
	cdx = 0.0f;
	cdy = 0.0f;
	characterframeno = 0;
	characterframecounter = 0;
	characterframecounterlimit = 4;
	keystate = 0;
	cammarginleft = getWidth() / 4;
	cammarginright = getWidth() - (getWidth() / 4);
	cammargintop = getHeight() / 4;
	cammarginbottom = getHeight() - (getHeight() / 4);
	bgdst.set(0, 0, getWidth(), getHeight());
	bgsx = 0;
	bgsy = 0;
}


void GameCanvas::update() {
	moveCharacter();
	moveCamera();
}

void GameCanvas::draw() {
	drawBackground();
	drawCharacter();
	drawGui();
}

/**
 * Karakteri hareket ettiren fonksiyondur. Kullanicinin bastigi tuslari okuyarak karakteri buna gore
 * bir yone dogru hareket ettirme islemini yapar.
 */
void GameCanvas::moveCharacter() {
	// Tuslara basilip basilmadigini test ediyoruz. Basilmis ise karakterin delta x ve delta y
	// degerlerini hesapliyoruz.
	if ((keystate & KEY_A) != 0) { // Sagdan 2.bitte kayit olup olmadigini test ediyoruz.
		cdx += -std::cos(gDegToRad(crot)) * cspeed;
		cdy += -std:: sin(gDegToRad(crot)) * cspeed;
	} else if ((keystate & KEY_D) != 0) { // Sagdan 3.bitte kayit olup olmadigini test ediyoruz.
		cdx += std::cos(gDegToRad(crot)) * cspeed;
		cdy += std::sin(gDegToRad(crot)) * cspeed;
	}

	if ((keystate & KEY_W) != 0) { // Sagdan 4.bitte kayit olup olmadigini test ediyoruz.
		cdx += std::sin(gDegToRad(crot)) * cspeed;
		cdy += -std:: cos(gDegToRad(crot)) * cspeed;
	} else if ((keystate & KEY_S) != 0) { // Sagdan 5.bitte kayit olup olmadigini test ediyoruz.
		cdx += -std::sin(gDegToRad(crot)) * cspeed;
		cdy += std:: cos(gDegToRad(crot)) * cspeed;
	}

	// Hesaplanan karakter delta degerlerini karakterin koordinatlarina ekliyoruz
	cx += cdx;
	cy += cdy;

	// Karakter yururken cizdirilecek animasyon kare numarasini bir bir artiriyoruz
	if (cdx != 0.0f || cdy != 0.0f) {
		characterframecounter++;
		if (characterframecounter >= characterframecounterlimit) {
			characterframeno++;
			if (characterframeno >= characterframenum) characterframeno = 0;
			characterframecounter = 0;
		}
	} else {
		characterframeno = 0;
		characterframecounter = 0;
	}
}

/**
 * Bu fonksiyon kamera hareketini simule eder. Karakter kamera marjinlerine ulastiginda
 * kamera karakterle beraber hareket etmeye baslar. Kamera marjinlerinin icerisinde
 * kalindigi surece kamera hareket etmez.
 */
void GameCanvas::moveCamera() {
	// Kamera marjin degerlerini degisken olarak hesapliyoruz. Marjinlerin default
	// degerini ekran boyunun yarisi olarak hesapliyoruz. Haritanin kenarlarina ulasildi
	// ise kamera marjinlerini sifir degerini veriyoruz.
	cammarginleft = getWidth() >> 2;
	cammarginright = getWidth() - (getWidth() >> 2);
	cammargintop = getHeight() >> 2;
	cammarginbottom = getHeight() - (getHeight() >> 2);
	if (bgsx <= 0) {
		bgsx = 0;
		cammarginleft = 0;
	} else if (bgsx >= background.getWidth() - getWidth() - cspeed) {
		bgsx = background.getWidth() - getWidth() - cspeed;
		cammarginright = getWidth() - character[0].getWidth();
	}
	if (bgsy <= 0) {
		bgsy = 0;
		cammargintop = 0;
	} else if (bgsy >= background.getHeight() - getHeight() - cspeed) {
		bgsy = background.getHeight() - getHeight() - cspeed;
		cammarginbottom = getHeight() - character[0].getHeight();
	}

	// Karakterin kamera marjinlerine ulasip ulasmadigini test ediyoruz. Ulasmis ise
	// kamerayi ilerletiyoruz. Eger kamera harita sinirlarina ulasirsa, kamerayi
	// artik ilerletmiyoruz.
	if (cx < cammarginleft || cx >= cammarginright) {
		bgsx += cdx;
		cx -= cdx;
		if (bgsx < 0) {
			bgsx -= cdx;
			cx = cammarginleft;
		} else if (bgsx >= background.getWidth() - getWidth()) {
			bgsx -= cdx;
			cx = cammarginright;
		}

	}
	if (cy < cammargintop || cy >= cammarginbottom) {
		bgsy += cdy;
		cy -= cdy;
		if (bgsy < 0) {
			bgsy -= cdy;
			cy = cammargintop;
		} else if (bgsy >= background.getHeight() - getHeight()) {
			bgsy -= cdy;
			cy = cammarginbottom;
		}
	}

	// Karakter delta degerlerini sifirliyoruz.
	cdx = 0.0f; // Optimizasyon acisindan float degeri float olarak sifirlamak gerek
	cdy = 0.0f;
}

/**
 * Arkaplandaki harita cizdirilir.
 */
void GameCanvas::drawBackground() {
	bgsrc.set(bgsx, bgsy, bgsx + getWidth(), bgsy + getHeight());
	bgdst.set(0, 0, getWidth(), getHeight());
	background.drawSub(bgsrc, bgdst);
}

/**
 * Karakter ekrana cizdirilir. characterframeno degiskeni ekrana cizdirilecek gorsel karenin
 * numarasini gosterir.
 */
void GameCanvas::drawCharacter() {
	character[characterframeno].draw(cx, cy, cw, ch, crot);
}

/**
 * GUI ogeleri ekrana cizdirilir.
 */
void GameCanvas::drawGui() {

}

void GameCanvas::keyPressed(int key) {
	//logi("GC", "keyPressed:" + gToStr(key));
	keyno = -1;
	switch(key) {
	case 65: // Key A
		keyno = KEY_A; //Sagdan 2.bite kayit yapiyoruz.
		break;
	case 68: // Key D
		keyno = KEY_D; //Sagdan 3.bite kayit yapiyoruz.
		break;
	case 87: // Key W
		keyno = KEY_W; //Sagdan 4.bite kayit yapiyoruz.
		break;
	case 83: // Key S
		keyno = KEY_S; //Sagdan 5.bite kayit yapiyoruz.
		break;
	default:
		break;
	}
	if (keyno != -1) keystate |= keyno;
}

void GameCanvas::keyReleased(int key) {
	//logi("GC", "keyReleased:" + gToStr(key));
	keyno = -1;
		switch(key) {
		case 65: // Key A
			keyno = KEY_A; //Sagdan 2.bite kayit yapiyoruz.
			break;
		case 68: // Key D
			keyno = KEY_D; //Sagdan 3.bite kayit yapiyoruz.
			break;
		case 87: // Key W
			keyno = KEY_W; //Sagdan 4.bite kayit yapiyoruz.
			break;
		case 83: // Key S
			keyno = KEY_S; //Sagdan 5.bite kayit yapiyoruz.
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
	crot = (int)(gRadToDeg((float)std::atan2((float)(y - cy), (float)(x - cx))) + 90.0f + 360.0f) % 360;
}

void GameCanvas::mousePressed(int x, int y, int button) {
	crot = (int)(gRadToDeg((float)std::atan2((float)(y - cy), (float)(x - cx))) + 90.0f + 360.0f) % 360;
	//logi("crot :" + gToStr(crot));
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

// ### TERMS ###
// Coding Conventions
// Main Loop
// Synchronized / Asynchronized Functions
// Bitwise Operations
