#ifndef UTILS_CLASS_H
#define UTILS_CLASS_H

#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <glm/glm.hpp>

class Utils {

public:
    static std::string readFile(const char* filePath);
    static float calculateDistance(glm::vec3 a, glm::vec3 b);
    static void display(glm::vec3 vector);
    
};

#endif