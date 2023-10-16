#ifndef HOTBAR_CLASS_H
#define HOTBAR_CLASS_H

#include <stdint.h>

class Hotbar {
    private:
        int8_t blocks[9] = { -1 };
        int index = 0;
    public:
        static const int SIZE = 9;

        Hotbar() = default;

        int getIndex();
        void setIndex(int index);
        
        int getSelectedBlock();
        void setBlock(int index, int8_t block);

};

#endif