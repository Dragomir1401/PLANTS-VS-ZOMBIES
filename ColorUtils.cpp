#include "ColorUtils.hpp"

m1::ColorUtils::ColorUtils()
{
}

m1::ColorUtils::~ColorUtils()
{
}

int m1::ColorUtils::SelectHealthByColor(glm::vec3 color)
{
    // Determines enemy health by color  
    // purple - big
    // yellow - medium
    // blue - medium
    // orange - small
    if (color == glm::vec3(1.0f, 0.5f, 0.0f))
    {
        return 2;
    }
    else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return 4;
    }
    else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
    {
        return 6;
    }
    else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
    {
        return 8;
    }
    else
    {
        return 0;
    }

}

float m1::ColorUtils::SelectSpeedByColor(glm::vec3 color)
{
    // Determines enemy speed by color  
    // purple - big
    // yellow - medium
    // blue - medium
    // orange - small
    if (color == glm::vec3(1.0f, 0.5f, 0.0f))
    {
        return 0.3f;
    }
    else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return 0.3f;
    }
    else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
    {
        return 0.3f;
    }
    else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
    {
        return 0.3f;
    }
    else
    {
        return 0.3f;
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
    else if (color == glm::vec3(0.1f, 0.5f, 0.5f))
    {
		return 5;
	}
    else
    {
        return 0;
    }

}

int m1::ColorUtils::GetShooterCostByColor(glm::vec3 color)
{
    // Determines enemy speed by color  
    // purple - 4
    // yellow - 3
    // blue - 2
    // orange - 1
    // gold - 5
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
    else if (color == glm::vec3(1.0f, 0.85f, 0.5f))
    {
        return 5;
    }
    else if (color == glm::vec3(0.1f, 0.5f, 0.5f))
    {
		return 5;
	}
    else
    {
		return 0;
	}
}

int m1::ColorUtils::SelectRandomLine()
{
    // Returns a random int between 0 and 3
    return rand() % PLACINGS_SIZE;
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
        return 6;
    }
    else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return 4;
    }
    else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
    {
        return 4;
    }
    else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
    {
        return 3;
    }
    else if (color == glm::vec3(0.1f, 0.5f, 0.5f))
    {
        return 4;
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
        return 10.0f;
    }
    else if (color == glm::vec3(0.0f, 0.0f, 1.0f))
    {
        return 14.0f;
    }
    else if (color == glm::vec3(1.0f, 1.0f, 0.0f))
    {
        return 15.0f;
    }
    else if (color == glm::vec3(0.6f, 0.0f, 1.0f))
    {
        return 16.0f;
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
    case 4:
        return glm::vec3(1.0f, 0.85f, 0.5f);
    case 5:
        return glm::vec3(0.1f, 0.5f, 0.5f);
    default:
        return glm::vec3(0, 0, 0);
    }

}

