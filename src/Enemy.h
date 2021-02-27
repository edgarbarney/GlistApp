/*
 * Enemy.h
 *
 *  Created on: 27 Þub 2021
 *      Author: kiwim
 */

#ifndef SRC_ENEMY_H_
#define SRC_ENEMY_H_

class Enemy {
public:
	Enemy();
	Enemy(const Enemy& original);
	virtual ~Enemy();
	void setPosition(int x, int y);
	void setRotation(float rotation);
	void setFrameNo(int frameNo);
	int getX();
	int getY();
	float getRotation();
	int getFrameNo();

private:
	int x, y;
	float rotation;
	int frameno;
};

#endif /* SRC_ENEMY_H_ */
