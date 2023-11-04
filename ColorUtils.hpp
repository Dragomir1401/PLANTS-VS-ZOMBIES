#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/StaticScene.hpp"
#define TYPES_OF_SHOOTERS 4

namespace m1
{
	class ColorUtils
	{
	public:
		ColorUtils();
		~ColorUtils();
		int SelectHealthByColor(glm::vec3 color);
		float SelectSpeedByColor(glm::vec3 color);
		int SelectShootingPowerByColor(glm::vec3 color);
		int GetShooterCostByColor(glm::vec3 color);
		int SelectRandomLine();
		int GetTypeByColor(glm::vec3 color);
		int GetBulletIntervalByColor(glm::vec3 color);
		float GetSpawnIntervalByColor(glm::vec3 color);
		glm::vec3 getRandomColor();
		glm::vec3 SelectColor(int index);
		float getRandomFloat(float min, float max);
	};
} // namespace colorutils