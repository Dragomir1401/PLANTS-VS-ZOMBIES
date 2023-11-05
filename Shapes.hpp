#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace shapes
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
    Mesh* CreateShooter(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateHeart(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 colorInside, glm::vec3 colorOutside, bool fill = false);
    Mesh* CreateSpawner(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill);
    Mesh* CreateCannon(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill);
    Mesh* CreateRocket(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, bool fill);
    Mesh* CreateEater(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill);
    Mesh* CreateSnowCannon(const std::string& name, glm::vec3 center, float length, glm::vec3 colorOutside, glm::vec3 colorInside, bool fill);
} // namespace shapes
