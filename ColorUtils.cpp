#include "ColorUtils.hpp"

m1::ColorUtils::ColorUtils()
{
}

m1::ColorUtils::~ColorUtils()
{
}

int m1::ColorUtils::selectHealthByColor(glm::vec3 color)
    {
        // Determines enemy health by color  
        // purple - big
        // yellow - medium
        // blue - medium
        // orange - small
        if (color == glm::vec3(1.0f, 0.5f, 0.0f))
        {
            return 1;
        }
        else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
        {
            return 3;
        }
        else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
        {
            return 5;
        }
        else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
        {
            return 7;
        }
        else
        {
            return 0;
        }

    }

    int m1::ColorUtils::selectSpeedByColor(glm::vec3 color)
    {
        // Determines enemy health by color  
        // purple - big
        // yellow - medium
        // blue - medium
        // orange - small
        if (color == glm::vec3(1.0f, 0.5f, 0.0f))
        {
            return 1;
        }
        else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
        {
            return 2;
        }
        else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
        {
            return 2;
        }
        else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
        {
            return 3;
        }
        else
        {
            return 0;
        }

    }

    int m1::ColorUtils::SelectShootingPowerByColor(glm::vec3 color)
    {
        if (color == glm::vec3(1.0f, 0.5f, 0.0f))
        {
            return 1;
        }
        else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
        {
            return 2;
        }
        else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
        {
            return 3;
        }
        else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
        {
            return 4;
        }
        else
        {
            return 0;
        }

    }

    int m1::ColorUtils::GetTypeByColor(glm::vec3 color)
    {
        if (color == glm::vec3(1.0f, 0.5f, 0.0f))
        {
            return 0;
        }
        else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
        {
            return 1;
        }
        else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
        {
            return 2;
        }
        else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }

    int m1::ColorUtils::GetBulletIntervalByColor(glm::vec3 color)
    {
        if (color == glm::vec3(1.0f, 0.5f, 0.0f))
        {
            return 4;
        }
        else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
        {
            return 3;
        }
        else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
        {
            return 3;
        }
        else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }

    float m1::ColorUtils::GetSpawnIntervalByColor(glm::vec3 color)
    {
        // Determines spawn interval by color   
        // purple - rare
        // yellow - medium
        // blue - medium
        // orange - common

        if (color == glm::vec3(1.0f, 0.5f, 0.0f))
        {
            return 6.0f;
        }
        else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
        {
            return 8.0f;
        }
        else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
        {
            return 9.0f;
        }
        else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
        {
            return 11.0f;
        }
        else
        {
            return 0.0f;
        }
    }

    float m1::ColorUtils::getRandomFloat(float min, float max)
    {
        // Return random float between min and max
        return ((float)rand() / RAND_MAX) * (max - min) + min;
    }

    glm::vec3 m1::ColorUtils::getRandomColor()
    {
        // Returns random color between orange, blue, yellow and purple
        int random = rand() % TYPES_OF_SHOOTERS;
        switch (random)
        {
        case 0:
            return glm::vec3(1.0f, 0.5f, 0.0f);
            break;
        case 1:
            return glm::vec3(0.0f, 0.0f, 1.0f);
            break;
        case 2:
            return glm::vec3(1.0f, 1.0f, 0.0f);
            break;
        case 3:
            return glm::vec3(0.6f, 0.0f, 1.0f);
            break;
        default:
            return glm::vec3(1.0f, 1.5f, 1.0f);
            break;
        }
    }

    glm::vec3 m1::ColorUtils::SelectColor(int index)
    {
        switch (index)
        {
        case 0:
            return  glm::vec3(1.0f, 0.5f, 0.0f);
        case 1:
            return glm::vec3(0.0f, 0.0f, 1.0f);
        case 2:
            return glm::vec3(1.0f, 1.0f, 0.0f);
        case 3:
            return glm::vec3(0.6f, 0.0f, 1.0f);
        default:
            return glm::vec3(0, 0, 0);
        }

    }

