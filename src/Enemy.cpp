/*
 * Enemy.cpp
 *
 *  Created on: 27 Þub 2021
 *      Author: kiwim
 */

#include "Enemy.h"


Enemy::Enemy() {
	x = 0;
	y = 0;
	rotation = 0.0f;
	frameno = 0;
}

Enemy::Enemy(const Enemy& original) {
	x = original.x;
	y = original.y;
	rotation = original.rotation;
	frameno = original.frameno;
}

Enemy::~Enemy() {

}

void Enemy::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void Enemy::setRotation(float rotation) {
	this->rotation = rotation;
}

void Enemy::setFrameNo(int frameNo) {
	frameno = frameNo;
}

int Enemy::getX() {
	return x;
}

int Enemy::getY() {
	return y;
}

float Enemy::getRotation() {
	return rotation;
}

int Enemy::getFrameNo() {
	return frameno;
}




