#include "game/Piece.hpp"
#include "game/Game.hpp"
#include <iostream>
#include <string.h>

using namespace std;

Piece::Piece(vector<array<int, 4>> shapes)
	: currentShape(0), shapes(), x(0), y(0) {
	array<array<int, 4>, 4> tmp{};
	for (const auto &shape : shapes) {
		memset(tmp.data(), 0, sizeof(tmp));
		for (int i = 0; i < 4; i++) {
			tmp[((int)shape[i] / 4)][shape[i] % 4] = 1;
		}
		this->shapes.push_back(tmp);
	}
}

void Piece::init(Renderer &renderer) {
	tmp = new Texture(renderer, "assets/texture/block/blue.png");
}

void Piece::update(double delta) {
}

void Piece::render(Renderer &renderer) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (shapes[currentShape][j][i] == 1) {
				renderer.draw(tmp, (x + i) * TILE_SIZE, (y + j) * TILE_SIZE,
							  TILE_SIZE, TILE_SIZE);
			}
		}
	}
}

void Piece::resize(int width, int height) {
}

void Piece::dispose() {
}

void Piece::rotate() {
	currentShape = (currentShape + 1) % shapes.size();
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
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
