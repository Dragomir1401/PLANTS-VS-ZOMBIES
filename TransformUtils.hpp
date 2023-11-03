#pragma once

#include "utils/glm_utils.h"


namespace transformUtils
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // TODO(student): Implement the translation matrix
        glm::mat3 translateMatrix = glm::mat3(0);

        translateMatrix[2][0] = translateX;
        translateMatrix[2][1] = translateY;

        translateMatrix[0][0] = 1;
        translateMatrix[1][1] = 1;
        translateMatrix[2][2] = 1;

        return translateMatrix;

    }

    inline glm::mat3 Translate(glm::vec2 translate)
    {
        // TODO(student): Implement the translation matrix
        glm::mat3 translateMatrix = glm::mat3(0);

        translateMatrix[2][0] = translate.x;
        translateMatrix[2][1] = translate.y;

        translateMatrix[0][0] = 1;
        translateMatrix[1][1] = 1;
        translateMatrix[2][2] = 1;

        return translateMatrix;

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        // TODO(student): Implement the scaling matrix
        glm::mat3 scaleMatrix = glm::mat3(0);

        scaleMatrix[0][0] = scaleX;
        scaleMatrix[1][1] = scaleY;
        scaleMatrix[2][2] = 1;

        return scaleMatrix;

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        // TODO(student): Implement the rotation matrix
        glm::mat3 rotateMatrix = glm::mat3(0);

        rotateMatrix[0][0] = cos(radians);
        rotateMatrix[0][1] = -sin(radians);
        rotateMatrix[1][0] = sin(radians);
        rotateMatrix[1][1] = cos(radians);
        rotateMatrix[2][2] = 1;

        return rotateMatrix;

    }
}   // namespace transformUtils
