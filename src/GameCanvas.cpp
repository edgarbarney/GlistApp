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


GameCanvas::GameCanvas(gBaseApp* root) : gBaseCanvas(root) {
}

GameCanvas::~GameCanvas() {
}

/**
 * Oyunda kullanilan tum degiskenlerin ilk degerleri burada verilir.
 */
void GameCanvas::setup() {
	logi("GlistApp setup 1");
	background.loadImage("oyun/haritalar/arkaplan1.jpg"); // Arkaplan resmini ekledik
	logi("GlistApp setup 2");
	levelmap.loadImage("oyun/haritalar/radar1.png");
	logi("GlistApp setup 3");
	healthbar.loadImage("oyun/gui/element_0076_Layer-78.png");
	healthbarbackground.loadImage("oyun/gui/element_0077_Layer-79.png");
	healthbarframe.loadImage("oyun/gui/element_0092_Layer-94.png");
	charactericon.loadImage("oyun/gui/erkekikon.png");
	healthicon.loadImage("oyun/gui/element_0098_Layer-100.png");
	enemyicon.loadImage("oyun/gui/element_0100_Layer-102.png");
	enemybar.loadImage("oyun/gui/element_0076_Layer-78b.png");
	for (int i = 0; i < characterframenum; i++) character[i].loadImage("oyun/karakterler/erkek/erkek_tufek_0" + gToStr(i) + ".png"); // Karakterimizi ekledik
	enemyanimationframenum[ENEMYANIMATION_WALK] = 8;
	enemyanimationframenum[ENEMYANIMATION_ATTACK] = 16;
	enemyanimationframenum[ENEMYANIMATION_DEATH] = 14;
	enemyanimationloop[ENEMYANIMATION_WALK] = true;
	enemyanimationloop[ENEMYANIMATION_ATTACK] = true;
	enemyanimationloop[ENEMYANIMATION_DEATH] = false;
	for (int i = 0; i < enemyanimationnum; i++) {
		std::string imagepath = "walk/Walk_0";
		if (i == ENEMYANIMATION_ATTACK) imagepath = "attack/attack1_0";
		else if (i == ENEMYANIMATION_DEATH) imagepath = "death/Death_0";
		for (int j = 0; j < enemyanimationframenum[i]; j++) {
			std::string imageno = gToStr(j);
			if (j < 10) imageno = "0" + imageno;
			enemyimage[i][j].loadImage("oyun/dusman/" + imagepath + imageno + ".png");
		}
	}
	mapcharactersign.loadImage("oyun/haritalar/radarisaret1.png");
	mapenemysign.loadImage("oyun/haritalar/radarisaret2.png");
	bullet[BULLETSENDER_CHARACTER].loadImage("oyun/objeler/mermi.png");
	bullet[BULLETSENDER_ENEMY].loadImage("oyun/objeler/mermi2.png");
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
	enemyw = enemyimage[0][0].getWidth();
	enemyh = enemyimage[0][0].getHeight();
	for (int i = 0; i < enemynum; i++) {
		do {
			enemy[i].setPosition(170 + gRandom(background.getWidth() - 340), 170 + gRandom(background.getHeight() - 340));
		} while (enemy[i].getX() < camw && enemy[i].getY() < camh);
		enemy[i].setRotation(0.0f);
		enemy[i].setAnimationNo(ENEMYANIMATION_WALK);
		enemy[i].setAnimationNum(enemyanimationnum);
		enemy[i].setFrameNo(gRandom(enemyframenum));
		enemy[i].setFrameNum(enemyframenum);
		enemy[i].setAnimationLoop(enemyanimationloop[ENEMYANIMATION_WALK]);
	}
	mapx = getWidth() - (levelmap.getHeight() / 2) - levelmap.getWidth();
	mapy = levelmap.getHeight() / 2;
	enemydx = 0.0f;
	enemydy = 0.0f;
	enemyspeed = 1.0f;
	enemynear = false;
	liveenemynum = enemynum;
	bulletspeed = cspeed * 2;
	bulletrange = 90;
	bulletw = bullet[BULLETSENDER_CHARACTER].getWidth();
	bulleth = bullet[BULLETSENDER_CHARACTER].getHeight();
	muzzledangle = gRadToDeg(std::atan2(0 - (character[0].getHeight() / 2), 43 - (character[0].getWidth() / 2))) + 90.0f;
	muzzleangle = crot + muzzledangle;
	muzzledistance = std::sqrt(std::pow(0 - (character[0].getHeight() / 2), 2) + std::pow(43 - (character[0].getWidth() / 2), 2));
	bsender = 0;
	font.loadFont("FreeSans.ttf", 24);
	handdangle[0] = -gRadToDeg(std::atan2(53 - (enemyimage[0][3].getHeight() / 2), 113 - (enemyimage[0][3].getWidth() / 2)));
	handdangle[1] = -gRadToDeg(std::atan2(91 - (enemyimage[0][7].getHeight() / 2), 109 - (enemyimage[0][7].getWidth() / 2)));
	handdistance[0] = std::sqrt(std::pow(57 - (enemyimage[0][3].getHeight() / 2), 2) + std::pow(113 - (enemyimage[0][3].getWidth() / 2), 2));
	handdistance[1] = std::sqrt(std::pow(91 - (enemyimage[0][7].getHeight() / 2), 2) + std::pow(109 - (enemyimage[0][7].getWidth() / 2), 2));
	chealth = 100;
	chealthcounter = 0;
	chealthcounterlimit = 5;
	charactericonx = levelmap.getHeight() / 2;
	charactericony = charactericonx;
	healthx = charactericon.getHeight() + levelmap.getHeight() / 2 + 20;
	healthy = levelmap.getHeight() / 2;
	healthbarframex = healthx + healthicon.getHeight() + 10;
	healthbarframey = (levelmap.getHeight() / 2) + (healthicon.getHeight() - healthbarframe.getHeight()) / 2;
	healthbarbackgroundx = healthbarframex + 4;
	healthbarbackgroundy = healthbarframey + 8;
	enemyiconx = healthx;
	enemyicony = levelmap.getHeight() / 2 + healthy;
	enemybarx = healthbarframex;
	enemybary = (healthbarframey + healthicon.getHeight()) + (enemyicon.getHeight() - healthbarframe.getHeight()) / 2;
	enemybarbackgroundx = healthbarbackgroundx;
	enemybarbackgroundy = enemybary + 8;
	logi("GlistApp setup 2");
}

void GameCanvas::update() {
	moveCharacter();
	moveCamera();
	moveEnemies();
	moveBullets();
}

void GameCanvas::draw() {
	drawBackground();
	drawEnemies();
	drawCharacter();
	drawBullets();
	drawLevelMap();
	drawGui();
	//font.drawText("FPS:" + gToStr(root->getFramerate()), 24, 24, 1);
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
		cdy += -std::cos(gDegToRad(crot)) * cspeed;
	} else if ((keystate & KEY_S) != 0) { // Sagdan 5.bitte kayit olup olmadigini test ediyoruz.
		cdx += -std::sin(gDegToRad(crot)) * cspeed;
		cdy += std::cos(gDegToRad(crot)) * cspeed;
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
	//Dusman pozisyon ve rotasyon degerlerinin hesaplanmasi
	for (int i = 0; i < enemynum; i++) {
		if (enemy[i].getX() + enemyw >= camx && enemy[i].getX() <= camx + camw && enemy[i].getY() + enemyh >= camy && enemy[i].getY() < camy + camh) {
			if (enemy[i].getAnimationNo() != ENEMYANIMATION_DEATH) {
				enemy[i].setRotation(gRadToDeg(std::atan2((cy + ccdy + camy) - (enemy[i].getY() + (enemyh >> 1)), (cx + ccdx + camx) - (enemy[i].getX() + (enemyw >> 1)))) - 90.0f);

				int previousanimationno = enemy[i].getAnimationNo();
				// Dusman karakterin yanindaysa animasyonun gecmesi
				enemynear = checkCollision(cx + 4 + camx, cy + 50 + camy, cx + 52 + camx, cy + 100 + camy, enemy[i].getX() + 49, enemy[i].getY() + 28, enemy[i].getX() + 117, enemy[i].getY() + 62);
				if (enemynear) {
					enemy[i].setAnimationNo(ENEMYANIMATION_ATTACK);
					chealthcounter++;
					if (chealthcounter >= chealthcounterlimit) {
						chealth--;
						if (chealth <= 0) {
							chealth = 0;
							logi("Oyunu Kaybettiniz");
						}
						chealthcounter = 0;
					}
				} else {
					enemydx = -std::sin(gDegToRad(enemy[i].getRotation())) * enemyspeed;
					enemydy = std::cos(gDegToRad(enemy[i].getRotation())) * enemyspeed;
					enemy[i].setPosition(enemy[i].getX() + enemydx, enemy[i].getY() + enemydy);
					enemy[i].setAnimationNo(ENEMYANIMATION_WALK);
				}
				enemy[i].setFrameNum(enemyanimationframenum[enemy[i].getAnimationNo()]);
				if (enemy[i].getAnimationNo() != previousanimationno) enemy[i].setFrameNo(0);
				enemy[i].setAnimationLoop(enemyanimationloop[enemy[i].getAnimationNo()]);
			}

			//Dusman gorselinin oynatilmasi
			enemy[i].nextFrame();
			if (enemy[i].getAnimationNo() == ENEMYANIMATION_WALK && (enemy[i].getFrameNo() == 3 || enemy[i].getFrameNo() == 7) && enemy[i].getPreviousFrameNo() != enemy[i].getFrameNo()) {
				int handno = 0;
				if (enemy[i].getFrameNo() == 7) handno = 1;
				float nbx = std::sin(gDegToRad(enemy[i].getRotation() + handdangle[handno])) * handdistance[handno];
				float nby = std::cos(gDegToRad(enemy[i].getRotation() + handdangle[handno])) * handdistance[handno];
				float bx = enemy[i].getX() + ((enemyimage[0][0].getWidth() - bullet[BULLETSENDER_ENEMY].getWidth()) / 2) + nbx;
				float by = enemy[i].getY() + ((enemyimage[0][0].getHeight() - bullet[BULLETSENDER_ENEMY].getHeight()) / 2) + nby;
				float bdx = -std::sin(gDegToRad(enemy[i].getRotation())) * bulletspeed;
				float bdy = std::cos(gDegToRad(enemy[i].getRotation())) * bulletspeed;
				float brot = enemy[i].getRotation();
				generateBullet(bx, by, bdx, bdy, brot, BULLETSENDER_ENEMY);
			}
		}
	}
}

void GameCanvas::moveBullets() {
	if (bullets.empty()) return;
	int bulletnum = bullets.size();
	for (int i = bulletnum - 1; i >= 0; i--) {
		// Mermiyi ilerletiyoruz
		bullets[i][0] += bullets[i][2];
		bullets[i][1] += bullets[i][3];
		bullets[i][4]++;
		if (bullets[i][4] >= bulletrange || bullets[i][0] + bulletw - camx < 0 || bullets[i][0] - camx >= camw || bullets[i][1] - camy + bulleth < 0 || bullets[i][1] - camy >= camh) {
			bullets.erase(bullets.begin() + i);
			continue;
		}

		// Mermiye dusmanlarla carpismaþma testi yapiyoruz
		if (bullets[i][6] == BULLETSENDER_CHARACTER) {
			for (int j = 0; j < enemynum; j++) {
				if (enemy[j].getAnimationNo() != ENEMYANIMATION_DEATH) {
					bool enemyhit = checkCollision(bullets[i][0], bullets[i][1], bullets[i][0] + bulletw, bullets[i][1] + bulleth,
						enemy[j].getX(), enemy[j].getY(), enemy[j].getX() + enemyw, enemy[j].getY() + enemyh);
					if (enemyhit) {
						enemy[j].setAnimationNo(ENEMYANIMATION_DEATH);
						enemy[j].setFrameNo(0);
						enemy[j].setAnimationLoop(enemyanimationloop[enemy[j].getAnimationNo()]);
						enemy[j].setFrameNum(enemyanimationframenum[enemy[j].getAnimationNo()]);
						liveenemynum--;
						if (liveenemynum == 0) logi("Oyunu Kazandiniz");
						bullets.erase(bullets.begin() + i);
						break;
					}
				}
			}
		} else {
			bool characterhit = checkCollision(bullets[i][0], bullets[i][1], bullets[i][0] + bulletw, bullets[i][1] + bulleth,
					cx + camx, cy + camy, cx + camx + cw, cy + camy + ch);
			if (characterhit) {
				chealth--;
				if (chealth <= 0) {
					chealth = 0;
					logi("Oyunu Kaybettiniz 2");
				}
				bullets.erase(bullets.begin() + i);
				break;
			}
		}
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
	for (int i = 0; i < enemynum; i++) if (enemy[i].getAnimationNo() != ENEMYANIMATION_DEATH) mapenemysign.draw(mapx + 2 + ((int)enemy[i].getX() >> 5), mapy + 2 + ((int)enemy[i].getY() >> 5));
	mapcharactersign.draw(mapx + 2 + (((int)cx + camx) >> 5), mapy + 2 + (((int)cy + camy) >> 5));
}

/**
 * Karakter ekrana cizdirilir. characterframeno degiskeni ekrana cizdirilecek gorsel karenin
 * numarasini gosterir.
 */
void GameCanvas::drawCharacter() {
	character[characterframeno].draw(cx, cy, cw, ch, crot);
}

void GameCanvas::drawEnemies() {
	for (int i = 0; i < enemynum; i++) enemyimage[enemy[i].getAnimationNo()][enemy[i].getFrameNo()].draw(enemy[i].getX() - camx, enemy[i].getY() - camy, enemyimage[0][0].getWidth(), enemyimage[0][0].getHeight(), enemy[i].getRotation());
}

void GameCanvas::drawBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bsender = (int)bullets[i][6];
		bullet[bsender].draw(bullets[i][0] - camx, bullets[i][1] - camy, bullet[bsender].getWidth(), bullet[bsender].getHeight(), bullets[i][5]);
	}
}

/**
 * GUI ogeleri ekrana cizdirilir.
 */
void GameCanvas::drawGui() {
	charactericon.draw(charactericonx, charactericony);
	healthicon.draw(healthx, healthy);
	healthbarframe.draw(healthbarframex, healthbarframey);
	healthbarbackground.draw(healthbarbackgroundx, healthbarbackgroundy);
	healthbar.drawSub(healthbarbackgroundx, healthbarbackgroundy, healthbar.getWidth() * chealth / 100, healthbar.getHeight(),
			0, 0, healthbar.getWidth() * chealth / 100, healthbar.getHeight());
	enemyicon.draw(enemyiconx, enemyicony);
	healthbarframe.draw(enemybarx, enemybary);
	healthbarbackground.draw(enemybarbackgroundx, enemybarbackgroundy);
	enemybar.drawSub(enemybarbackgroundx, enemybarbackgroundy, enemybar.getWidth() * liveenemynum / enemynum, enemybar.getHeight(),
				0, 0, enemybar.getWidth() * liveenemynum / enemynum, enemybar.getHeight());
	//enemybar.draw(enemybarx, enemybary);
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
	crot = gRadToDeg(std::atan2(y - (cy + (character[0].getHeight() / 2)), x - (cx + (character[0].getWidth())))) + 90.0f;
	muzzleangle = crot + muzzledangle;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	logi("mouseDragged x:" + gToStr(x) + ", y:" + gToStr(y) + ", b:" + gToStr(button));
}

void GameCanvas::mousePressed(int x, int y, int button) {
	//logi("crot :" + gToStr(crot));
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	logi("GC", "mouseReleased, button:" + gToStr(button));
	float nbx = std::sin(gDegToRad(muzzleangle)) * muzzledistance;
	float nby = -std::cos(gDegToRad(muzzleangle)) * muzzledistance;
	float bx = cx + ((cw - bullet[BULLETSENDER_CHARACTER].getWidth()) / 2) + nbx + camx; // x
	float by = cy + ((ch - bullet[BULLETSENDER_CHARACTER].getHeight()) / 2) + nby + camy; // y
	float bdx = std::sin(gDegToRad(crot)) * bulletspeed; // dx
	float bdy = -std::cos(gDegToRad(crot)) * bulletspeed; // dy
	float brot = crot;
	generateBullet(bx, by, bdx, bdy, brot, BULLETSENDER_CHARACTER);
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

bool GameCanvas::checkCollision(int xLeft1, int yUp1, int xRight1, int yBottom1, int xLeft2, int yUp2, int xRight2, int yBottom2) {
	if(xLeft1 < xRight2 && xRight1 > xLeft2 && yBottom1 > yUp2 && yUp1 < yBottom2) {
		return true;
    }
    return false;
}

void GameCanvas::generateBullet(float bulletx, float bullety, float bulletdx, float bulletdy, float bulletrotation, int bulletSender) {
	// Yeni bir mermi uretiyoruz
	std::vector<float> newbullet;
	newbullet.push_back(bulletx); // x
	newbullet.push_back(bullety); // y
	newbullet.push_back(bulletdx); // dx
	newbullet.push_back(bulletdy); // dy
	newbullet.push_back(0); // ilerleme miktari
	newbullet.push_back(bulletrotation);
	newbullet.push_back(bulletSender);

	// Yeni mermiyi mermiler vektorune ekliyoruz
	bullets.push_back(newbullet);
}

// ### TERMS ###
// Coding Conventions
// Main Loop
// Synchronized / Asynchronized Functions
// Bitwise Operations
