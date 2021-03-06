#include "gui/Gui.hpp"

Gui::Gui(): removed(false), visible(true) {

}

void Gui::remove() {
    removed = true;
}

void Gui::setVisible(bool visible) {
    this->visible = visible;
}

bool Gui::shouldRemove() {
    return removed;
}