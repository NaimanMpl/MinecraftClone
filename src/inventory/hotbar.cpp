#include "inventory/hotbar.h"

void Hotbar::setIndex(int index) {
    this->index = index;
}

int Hotbar::getIndex() {
    return this->index;
}

int Hotbar::getSelectedBlock() {
    return blocks[index];
}

void Hotbar::setBlock(int index, int8_t block) {
    blocks[index] = block;
}