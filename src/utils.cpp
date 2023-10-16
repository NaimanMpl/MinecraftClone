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

Material Utils::getMaterialFromBlock(int8_t block) {
    switch (block) {
        case -1:
            return Material::AIR;
        case 0:
            return Material::DIRT;
        case 1:
            return Material::BRICK;
        case 2:
            return Material::STONE;
        case 3:
            return Material::SAND;
        case 4:
            return Material::WOOD;
        case 5:
            return Material::WOOL;
        case 6:
            return Material::DIAMOND;
        case 7:
            return Material::WATER;
        case 8:
            return Material::SNOW;
        case 9:
            return Material::LEAVE;
        case 10:
            return Material::GRASS;
        case 11:
            return Material::OAK_WOOD;
        case 12:
            return Material::CACTUS;
        default:
            return Material::AIR;
    }
}
