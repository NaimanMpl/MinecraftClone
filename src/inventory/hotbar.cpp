#include "inventory/hotbar.h"

void Hotbar::setIndex(int index) {
    this->index = index;
}

int Hotbar::getIndex() {
    return this->index;
}

Block* Hotbar::getSelectedBlock() {
    return blocks[index];
}

void Hotbar::setBlock(int index, Block* block) {
    blocks[index] = block;
}