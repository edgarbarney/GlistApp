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
	background.loadImage("oyun/haritalar/arkaplan1.jpg"); // Arkaplan resmini ekledik
	levelmap.loadImage("oyun/haritalar/radar1.jpg");
	for (int i = 0; i < characterframenum; i++) character[i].loadImage("oyun/karakterler/erkek/erkek_tufek_0" + gToStr(i) + ".png"); // Karakterimizi ekledik
	enemy.loadImage("oyun/dusman/walk/Walk_000.png");
	mapcharactersign.loadImage("oyun/haritalar/radarisaret1.png");
	mapenemysign.loadImage("oyun/haritalar/radarisaret2.png");
	crot = 0.0f;
	cx = (getWidth() - character[0].getWidth()) >> 1;
	cy = (getHeight() - character[0].getHeight()) >> 1;
	cw = character[0].getWidth();
	ch = character[0].getHeight();
	ccdx = 26;
	ccdy = 78;
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
	camw = getWidth();
	camh = getHeight();
	camx = 0;
	camy = 0;
	enemyw = enemy.getWidth() / 2;
	enemyh = enemy.getHeight() / 2;
	for (int i = 0; i < enemynum; i++) {
		do {
			enemyx[i] = 170 + gRandom(background.getWidth() - 340);
			enemyy[i] = 170 + gRandom(background.getHeight() - 340);
		} while (enemyx[i] < camw && enemyy[i] < camh);
		enemyrot[i] = 0.0f;
	}
	mapx = getWidth() - (levelmap.getHeight() / 2) - levelmap.getWidth();
	mapy = levelmap.getHeight() / 2;
}


void GameCanvas::update() {
	moveCharacter();
	moveCamera();
	moveEnemies();
}

void GameCanvas::draw() {
	drawBackground();
	drawEnemies();
	drawCharacter();
	drawLevelMap();
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
		cdy += -std::sin(gDegToRad(crot)) * cspeed;
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
	if (camx <= 0) {
		camx = 0;
		cammarginleft = 0;
	} else if (camx >= background.getWidth() - getWidth()) {
		camx = background.getWidth() - getWidth();
		cammarginright = getWidth() - character[0].getWidth();
	}
	if (camy <= 0) {
		camy = 0;
		cammargintop = 0;
	} else if (camy >= background.getHeight() - getHeight()) {
		camy = background.getHeight() - getHeight();
		cammarginbottom = getHeight() - character[0].getHeight();
	}

	// Karakterin kamera marjinlerine ulasip ulasmadigini test ediyoruz. Ulasmis ise
	// kamerayi ilerletiyoruz. Eger kamera harita sinirlarina ulasirsa, kamerayi
	// artik ilerletmiyoruz.
	if (cx < cammarginleft || cx >= cammarginright) {
		camx += cdx;
		cx -= cdx;
		if (camx < 0) {
			camx = 0;
			cx = cammarginleft;
		} else if (camx >= background.getWidth() - getWidth()) {
			camx = background.getWidth() - getWidth();
			cx = cammarginright;
		}

	}
	if (cy < cammargintop || cy >= cammarginbottom) {
		camy += cdy;
		cy -= cdy;
		if (camy < 0) {
			camy = 0;
			cy = cammargintop;
		} else if (camy >= background.getHeight() - getHeight()) {
			camy = background.getHeight() - getHeight();
			cy = cammarginbottom;
		}
	}

	// Karakter delta degerlerini sifirliyoruz.
	cdx = 0.0f; // Optimizasyon acisindan float degeri float olarak sifirlamak gerek
	cdy = 0.0f;
}

void GameCanvas::moveEnemies() {
	for (int i = 0; i < enemynum; i++) {
		enemyrot[i] = gRadToDeg(std::atan2((cy + ccdy + camy) - (enemyy[i] + (enemyh >> 1)), (cx + ccdx + camx) - (enemyx[i] + (enemyw >> 1)))) - 90.0f;
	}
}

/**
 * Arkaplandaki harita cizdirilir.
 */
void GameCanvas::drawBackground() {
	bgsrc.set(camx, camy, camx + camw, camy + camh);
	bgdst.set(0, 0, getWidth(), getHeight());
	background.drawSub(bgsrc, bgdst);
}

void GameCanvas::drawLevelMap() {
	levelmap.draw(mapx, mapy);
	for (int i = 0; i < enemynum; i++) mapenemysign.draw(mapx + 2 + (enemyx[i] >> 5), mapy + 2 + (enemyy[i] >> 5));
	mapcharactersign.draw(mapx + 2 + ((cx + camx) >> 5), mapy + 2 + ((cy + camy) >> 5));
}

/**
 * Karakter ekrana cizdirilir. characterframeno degiskeni ekrana cizdirilecek gorsel karenin
 * numarasini gosterir.
 */
void GameCanvas::drawCharacter() {
	character[characterframeno].draw(cx, cy, cw, ch, crot);
}

void GameCanvas::drawEnemies() {
	for (int i = 0; i < enemynum; i++) enemy.draw(enemyx[i] - camx, enemyy[i] - camy, enemy.getWidth(), enemy.getHeight(), enemyrot[i]);
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
