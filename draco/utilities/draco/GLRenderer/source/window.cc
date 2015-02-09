#include "window.h"

using namespace std;

GameWindow::GameWindow(int x, int y) {
	width = x;
	height = y;

}

unsigned int GameWindow::getWidth() {
	return width;
}

unsigned int GameWindow::getHeight() {
	return height;
}

void GameWindow::setWidth(unsigned int x) {
	width = x;
}

void GameWindow::setHeight(unsigned int y) {
	height = y;
}