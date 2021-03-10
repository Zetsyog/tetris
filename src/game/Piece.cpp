#include "game/Piece.hpp"
#include <iostream>
#include <string.h>

using namespace std;

Piece::Piece(vector<array<int, 4>> shapes) : currentShape(0), shapes() {
	array<array<int, 4>, 4> tmp{};
	for (const auto &shape : shapes) {
		memset(tmp.data(), 0, sizeof(tmp));
		for (int i = 0; i < 4; i++) {
			tmp[((int)shape[i] / 4)][shape[i] % 4] = 1;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << tmp[i][j] << " ";
			}
			cout << endl;
		}
		this->shapes.push_back(tmp);
	}
	cout << "yo" << endl;
}

void Piece::init(Renderer &renderer) {
	tmp = new Texture(renderer, "assets/texture/block/blue.png");
}

void Piece::update(double delta) {
}

void Piece::render(Renderer &renderer) {
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (shapes[currentShape][y][x] == 1) {
				renderer.draw(tmp, x * 64, y * 64);
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << shapes[currentShape][i][j] << " ";
		}
		cout << endl;
	}
}
