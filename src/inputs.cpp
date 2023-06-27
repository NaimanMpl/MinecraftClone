#include <GLFW/glfw3.h>
#include "inputs.h"

Inputs::Inputs() {

}

void Inputs::setDefaultSettings() {
    bind(Action::MOVE_FORWARD, GLFW_KEY_W);
    bind(Action::MOVE_LEFT, GLFW_KEY_A);
    bind(Action::MOVE_BACKWARD, GLFW_KEY_S);
    bind(Action::MOVE_RIGHT, GLFW_KEY_D);
    bind(Action::JUMP, GLFW_KEY_SPACE);
}

void Inputs::bind(Action action, int key) {
    keys[action] = key;
}

void Inputs::unbind(Action action) {
    keys.erase(action);
}