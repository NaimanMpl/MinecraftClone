#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include <tr1/unordered_map>

enum Action {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP
};

class Inputs {

    private:
        std::tr1::unordered_map<Action, int> keys;
        Inputs();
    
    public:
        static Inputs& getInstance() {
            static Inputs instance;
            return instance;
        }
        Inputs(const Inputs&) = delete;
        void operator=(const Inputs&) = delete;
        void bind(Action action, int key);
        void unbind(Action action);
        void setDefaultSettings();


};

#endif