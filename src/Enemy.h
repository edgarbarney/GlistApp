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
	void setPosition(float x, float y);
	void setRotation(float rotation);
	void setFrameNo(int frameNo);
	float getX();
	float getY();
	float getRotation();
	int getFrameNo();
	int getPreviousFrameNo();

	void setAnimationNo(int animationNo);
	void setAnimationNum(int animationNum);
	int getAnimationNo();
	int getAnimationNum();

	void setAnimationLoop(bool isLoop);
	bool getAnimationLoop();

	void setFrameNum(int frameNum);
	int getFrameNum();

	void setFrameCounter(int frameCounter);
	void setFrameCounterLimit(int frameCounterLimit);
	int getFrameCounter();
	int getFrameCounterLimit();
	void nextFrame();

private:
	float x, y;
	float rotation;
	int animationno, animationnum;
	int frameno, framenum, previousframeno;
	int framecounter;
	int framecounterlimit;
	bool animationloop;
};

#endif /* SRC_ENEMY_H_ */
