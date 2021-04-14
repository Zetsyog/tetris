#ifndef LAYOUT_H
#define LAYOUT_H

#include "graphics/Drawable.hpp"

enum PosSystem { Absolute, Relative };

class Gui : public Drawable {
  protected:
	int x, y, width, height;
	int _offsetX, _offsetY;
	bool _centerX, _centerY;
	PosSystem XPosSystem, YPosSystem;

  public:
	Gui();
	Gui(int x, int y, int width, int height);
	virtual ~Gui();

	virtual void resize(int width, int height);

	virtual int getX() const;
	virtual int getY() const;
	virtual int getWidth() const;
	virtual int getHeight() const;

	virtual void setWidth(int width);
	virtual void setHeight(int height);

	Gui *center();
	Gui *centerX();
	Gui *centerY();
	Gui *offset(int x, int y);
	Gui *offsetX(int x);
	Gui *offsetY(int y);
	Gui *absolute(int x, int y);
	Gui *absoluteX(int x);
	Gui *absoluteY(int y);
};

#endif
