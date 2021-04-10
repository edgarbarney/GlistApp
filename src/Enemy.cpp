/*
 * Enemy.cpp
 *
 *  Created on: 27 Þub 2021
 *      Author: mcan_
 */

#include "Enemy.h"
#include "gObject.h"


Enemy::Enemy() {
	x = 0;
	y = 0;
	rotation = 0.0f;
	animationno = 0;
	animationnum = 0;
	frameno = 0;
	previousframeno = 0;
	framenum = 0;
	framecounter = 0;
	framecounterlimit = 3;
	animationloop = true;
	//std::cout << "default constructor" << std::endl;
}

Enemy::Enemy(const Enemy& original) {
	x = original.x;
	y = original.y;
	rotation = original.rotation;
	animationno = original.animationno;
	animationnum = original.animationnum;
	frameno = original.frameno;
	previousframeno = original.previousframeno;
	framenum = original.framenum;
	framecounter = original.framecounter;
	framecounterlimit = original.framecounterlimit;
	animationloop = original.animationloop;
	//std::cout << "copy constructor" << std::endl;
}

Enemy::~Enemy() {

}

void Enemy::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void Enemy::setRotation(float rotation) {
	this->rotation = rotation;
}

void Enemy::setFrameNo(int frameNo) {
	frameno = frameNo;
}

float Enemy::getX() {
	return x;
}

float Enemy::getY() {
	return y;
}

float Enemy::getRotation() {
	return rotation;
}

int Enemy::getFrameNo() {
	return frameno;
}

int Enemy::getPreviousFrameNo() {
	return previousframeno;
}

void Enemy::setAnimationNo(int animationNo) {
	animationno = animationNo;
}

void Enemy::setAnimationNum(int animationNum) {
	animationnum = animationNum;
}

int Enemy::getAnimationNo() {
	return animationno;
}

int Enemy::getAnimationNum() {
	return animationnum;
}

void Enemy::setAnimationLoop(bool isLoop) {
	animationloop = isLoop;
}

bool Enemy::getAnimationLoop() {
	return animationloop;
}

void Enemy::setFrameNum(int frameNum) {
	framenum = frameNum;
}

int Enemy::getFrameNum() {
	return framenum;
}

void Enemy::setFrameCounter(int frameCounter) {
	framecounter = frameCounter;
}

void Enemy::setFrameCounterLimit(int frameCounterLimit) {
	framecounterlimit = frameCounterLimit;
}

int Enemy::getFrameCounter() {
	return framecounter;
}

int Enemy::getFrameCounterLimit() {
	return framecounterlimit;
}

void Enemy::nextFrame() {
	framecounter++;
	previousframeno = frameno;
	if (framecounter >= framecounterlimit) {
		frameno++;
		if (frameno >= framenum) {
			if (animationloop) frameno = 0;
			else frameno = framenum - 1;
		}
		framecounter = 0;
	}

}







