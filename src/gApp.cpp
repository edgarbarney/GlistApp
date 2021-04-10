/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#include "gApp.h"
#include "MenuCanvas.h"


gApp::gApp() {
}

gApp::~gApp() {
}

void gApp::setup() {
	MenuCanvas *cnv = new MenuCanvas(this);
	appmanager->setCurrentCanvas(cnv);
}

void gApp::update() {
}
