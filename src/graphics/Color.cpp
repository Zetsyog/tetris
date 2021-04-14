#include "graphics/Color.hpp"

std::vector<Color> Color::colors = {};

Color::Color() : id(0), texture(nullptr) {
}

Color::Color(int id, Texture *texture) : id(id), texture(texture) {
}

Texture *Color::getTexture() const {
	return texture;
}

int Color::getId() const {
	return id;
}

void Color::setTexture(Texture *t) {
	this->texture = t;
}

void Color::setId(int id) {
	this->id = id;
}

Color Color::get(int id) {
	return colors.at(id);
}

void Color::init(ResourceManager &rm) {
	colors.push_back(Color(0, rm.get("texture:block:blue")));
	colors.push_back(Color(COLOR_BLUE, rm.get("texture:block:blue")));
	colors.push_back(Color(COLOR_CYAN, rm.get("texture:block:cyan")));
	colors.push_back(Color(COLOR_GREEN, rm.get("texture:block:green")));
	colors.push_back(Color(COLOR_ORANGE, rm.get("texture:block:orange")));
	colors.push_back(Color(COLOR_PURPLE, rm.get("texture:block:purple")));
	colors.push_back(Color(COLOR_RED, rm.get("texture:block:red")));
	colors.push_back(Color(COLOR_YELLOW, rm.get("texture:block:yellow")));
	colors.push_back(Color(COLOR_GHOST, rm.get("texture:block:ghost")));
}

bool operator==(Color const &a, Color const &b) {
	return a.getId() == b.getId();
}
