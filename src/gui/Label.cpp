#include "gui/Label.hpp"

Label::Label(std::string text) : text(text) {
	glyph = new FontGlyph(text);
	setWidth(glyph->getWidth());
	setHeight(glyph->getHeight());
}

Label::Label(std::string text, bool big) : text(text) {
	glyph = new FontGlyph(text, big);
	setWidth(glyph->getWidth());
	setHeight(glyph->getHeight());
}

void Label::render(Renderer &renderer) {
	renderer.drawText(glyph, x, y);
}
