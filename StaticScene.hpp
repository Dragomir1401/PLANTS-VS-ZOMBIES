#pragma once
#include <vector>
#include <iostream>
#include "components/simple_scene.h"
#include "lab_m1/tema1/TransformUtils.hpp"
#include "lab_m1/tema1/Shapes.hpp"
#include "lab_m1/tema1/MeshWrapper.hpp"
#include "lab_m1/tema1/MeshWrapperShooter.hpp"
#include "lab_m1/tema1/MeshWrapperBullet.hpp"
#include "lab_m1/tema1/MeshWrapperEnemy.hpp"
#include "lab_m1/tema1/MeshWrapperCoin.hpp"

#define PLACINGS_SIZE 3
#define INITIAL_X 30
#define INITIAL_Y 50
#define HEIGHT_OF_MATRIX 400
#define MATRIX_DISPLACEMENT 125
#define SHOOTER_DISPLACEMENT 175
#define HIT_BAR_LENGTH 350
#define HIT_BAR_WIDTH 60
#define PLACEHOLDERS_COUNT 4
#define PLACEHOLDERS_COUNT_TOTAL 5
#define HEALTH_POINTS_COUNT 3
#define DEFAULT_COINS_COUNT 10
#define PLACEHOLDERS_X 50
#define PLACEHOLDERS_Y 600
#define SHOOTER_SCALE 0.6
#define HEALTH_POINT_SCALE 0.7
#define HEALTH_POINTS_X 800
#define HEALTH_POINTS_Y 680
#define DEFAULT_SQUARE_SIDE 100
#define COINS_Y_DISPLACEMENT 75
#define DEFAULT_BULLET_SIZE 50
#define DEFAULT_STAR_COST_SIZE 25
#define COINS_COUNT_PER_ROW 15
#define DEFAULT_ENEMY_SIZE 50
#define MATRIX_CORNER_X 120
#define MATRIX_CORNER_Y 50

namespace m1
{
	class StaticScene
	{
	public:
		StaticScene();
		~StaticScene();
		void CreateStaticScene();
		void CreateSquareMatrix();
		void CreateHitBar();
		void CreateShooters();
		void CreateHealthPoints();
		void CreatePlaceHolders();
		MeshWrapper* getPlacing(int row, int col) const;
		MeshWrapper* getHitBar() const;
		std::vector<MeshWrapper*> getHealthPoints() const;
		std::vector<MeshWrapper*> getShooters() const;
		std::vector<MeshWrapper*> getPlaceHolders() const;

	private:
		std::vector<MeshWrapper*> placeHolders_;
		std::vector<MeshWrapper*> shooters_;
		MeshWrapper* placings_[PLACINGS_SIZE][PLACINGS_SIZE];
		std::vector<MeshWrapper*> healthPoints_;
		MeshWrapper* hitBar_;
		glm::vec3 corner_ = glm::vec3(0, 0, 0);

		double squareSide_ = DEFAULT_SQUARE_SIDE;
	};
} // namespace m1