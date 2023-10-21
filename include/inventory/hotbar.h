#ifndef HOTBAR_CLASS_H
#define HOTBAR_CLASS_H

#include <stdint.h>

static const int HOTBAR_SIZE = 9;

class Hotbar {
    private:
        int8_t blocks[HOTBAR_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
        int index = 0;
    public:

        Hotbar() = default;

        int8_t* getBlocks();

        int getIndex();
        void setIndex(int index);
        
        int8_t getSelectedBlock();
        void setBlock(int index, int8_t block);

};

#endif