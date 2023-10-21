#include "inventory/hotbar.h"

int8_t* Hotbar::getBlocks() {
    return this->blocks;
}

void Hotbar::setIndex(int index) {
    this->index = index;
}

int Hotbar::getIndex() {
    return this->index;
}

int8_t Hotbar::getSelectedBlock() {
    return blocks[index];
}

void Hotbar::setBlock(int index, int8_t block) {
    blocks[index] = block;
}