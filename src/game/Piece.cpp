#include "game/Piece.hpp"
#include "App.hpp"
#include "game/Game.hpp"
#include <iostream>
#include <string.h>

using namespace std;

Piece::Piece(vector<array<int, 4>> shapes, Texture *t)
	: currentShape(0), shapes(), x(0), y(0), tmp(t) {
	array<array<int, 4>, 4> tmp{};
	for (const auto &shape : shapes) {
		memset(tmp.data(), 0, sizeof(tmp));
		for (int i = 0; i < 4; i++) {
			tmp[shape[i] % 4][((int)shape[i] / 4)] = 1;
		}
		this->shapes.push_back(tmp);
	}
	calculateBounds();
}

void Piece::update(double delta) {
}

void Piece::render(Renderer &renderer) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shapes[currentShape][i][j] == 1) {
				renderer.draw(tmp, (x + i) * TILE_SIZE, (y + j) * TILE_SIZE,
							  TILE_SIZE, TILE_SIZE);
			}
		}
	}
}

array<array<int, 4>, 4> Piece::getCurrentShape() {
	return shapes[currentShape];
}

void Piece::resize(int width, int height) {
}

void Piece::rotate() {
	currentShape = (currentShape + 1) % shapes.size();
	calculateBounds();
}

void Piece::invRotate() {
	currentShape = (currentShape - 1) % shapes.size();
	if (currentShape < 0) {
		currentShape = shapes.size() - 1;
	}
	calculateBounds();
}

void Piece::calculateBounds() {
	int minX = 3;
	int minY = 3;
	int maxX = 0;
	int maxY = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shapes[currentShape][i][j] == 1) {
				minX = i < minX ? i : minX;
				minY = j < minY ? j : minY;
				maxX = i > maxX ? i : maxX;
				maxY = j > maxY ? j : maxY;
			}
		}
	}
	width  = maxX - minX + 1;
	height = maxY - minY + 1;
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
}

int Piece::getWidth() {
	return width;
}

int Piece::getHeight() {
	return height;
}

void Piece::setX(int x) {
	this->x = x;
}

void Piece::setY(int y) {
	this->y = y;
}

void Piece::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void Piece::print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << shapes[currentShape][j][i] << " ";
		}
		cout << endl;
	}
}
