#include "graphics/Drawable.hpp"

Drawable::Drawable(): visible(false) {

}

Drawable::~Drawable() {

}

void Drawable::setVisible(bool visible) {
    this->visible = visible;
}

bool Drawable::isVisible() {
    return visible;
}