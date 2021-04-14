#include "gui/Gui.hpp"

Gui::Gui()
	: x(0), y(0), width(0), height(0), _offsetX(0), _offsetY(0),
	  _centerX(false), _centerY(false), XPosSystem(Absolute),
	  YPosSystem(Absolute) {
}

Gui::Gui(int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height), _offsetX(0), _offsetY(0),
	  _centerX(false), _centerY(false), XPosSystem(Absolute),
	  YPosSystem(Absolute) {
}

int Gui::getX() const {
	return x;
}

int Gui::getY() const {
	return y;
}

int Gui::getWidth() const {
	return width;
}

int Gui::getHeight() const {
	return height;
}

void Gui::setWidth(int width) {
	this->width = width;
}

void Gui::setHeight(int height) {
	this->height = height;
}

Gui *Gui::center() {
	return centerX()->centerY();
}

Gui *Gui::centerX() {
	_centerX   = true;
	XPosSystem = Relative;
	return this;
}

Gui *Gui::centerY() {
	_centerY   = true;
	YPosSystem = Relative;
	return this;
}

Gui *Gui::offset(int x, int y) {
	return offsetX(x)->offsetY(y);
}

Gui *Gui::offsetX(int x) {
	_offsetX   = x;
	XPosSystem = Relative;
	return this;
}

Gui *Gui::offsetY(int y) {
	_offsetY   = y;
	YPosSystem = Relative;
	return this;
}

Gui *Gui::absolute(int x, int y) {
	absoluteX(x);
	absoluteY(y);
	return this;
}

Gui *Gui::absoluteX(int x) {
	this->x	   = x;
	XPosSystem = Absolute;
	return this;
}

Gui *Gui::absoluteY(int y) {
	this->y	   = y;
	YPosSystem = Absolute;
	return this;
}

void Gui::resize(int width, int height) {
	if (XPosSystem == Relative) {
		if (_centerX) {
			x = width / 2 - getWidth() / 2 + _offsetX;
		} else {
			x = _offsetX;
		}
	}
	if (YPosSystem == Relative) {
		if (_centerY) {
			y = height / 2 - getHeight() / 2 + _offsetY;
		} else {
			y = _offsetY;
		}
	}
}

Gui::~Gui() {
}