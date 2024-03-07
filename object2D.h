#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "lab_m1/Tema1/Utility.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false, bool ocuppied = false);
    Mesh* CreateStar(const std::string &name, glm::vec3 center2, float length, glm::vec3 color);
    Mesh* CreateTurret(const std::string &name, glm::vec3 center2, float length, glm::vec3 color);
    Mesh* CreateEnemy(const std::string &name, glm::vec3 center2, float length, glm::vec3 color);
    Mesh* CreateLife(const std::string& name, glm::vec3 center2, float length, glm::vec3 color);
    Mesh* CreateTank(const std::string& name, glm::vec3 center2, float length, glm::vec3 color);
    Mesh* CreateBonus(const std::string& name, glm::vec3 center2, float length);
    Mesh* CreateRoundHeart(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, int numPoints);
    Mesh* CreateBonusLife(const std::string& name, glm::vec3 center2, float length);
    Mesh* CreateLetter(const std::string& name, glm::vec3 center2, float length, glm::vec3 color);


    
}
