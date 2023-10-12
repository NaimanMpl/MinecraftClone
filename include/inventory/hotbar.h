#ifndef HOTBAR_CLASS_H
#define HOTBAR_CLASS_H

#include "world/block.h"

class Hotbar {
    private:
        Block* blocks[9] = { nullptr };
        int index = 0;
    public:
        static const int SIZE = 9;

        Hotbar() = default;

        int getIndex();
        void setIndex(int index);
        
        Block* getSelectedBlock();
        void setBlock(int index, Block* block);

};

#endif