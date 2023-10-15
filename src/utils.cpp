#include "utils.h"

std::string Utils::readFile(const char* filePath) {
    std::ifstream fileStream(filePath, std::ios::binary);

    if (!fileStream) {
        std::cerr << "Impossible de lire le fichier " << filePath << ". Le fichier n'existe pas" << std::endl;
        return "";
    }

    std::string content;
    fileStream.seekg(0, std::ios::end);
    content.resize(fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);
    fileStream.read(&content[0], content.size());
    fileStream.close();

    return content;
}

float Utils::calculateDistance(glm::vec3 a, glm::vec3 b) {
    return glm::length(a - b);
}

void Utils::display(glm::vec3 vector) {
    std::cout << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;
}