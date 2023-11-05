#include "StaticScene.hpp"

namespace m1
{
    StaticScene::StaticScene()
    {
        CreateStaticScene();
    }

    StaticScene::~StaticScene()
    {
    }

    void StaticScene::CreateStaticScene()
    {
        CreateSquareMatrix();
		CreateHitBar();
        CreateShooters();
        CreateHealthPoints();
        CreatePlaceHolders();
    }

    void StaticScene::CreateSquareMatrix() {
        double cx = corner_.x + squareSide_ / 2;
        double cy = corner_.y + squareSide_ / 2;

        MeshWrapper* square1 = new MeshWrapper(shapes::CreateSquare("square1", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[0][0] = square1;

        MeshWrapper* square2 = new MeshWrapper(shapes::CreateSquare("square2", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[0][1] = square2;

        MeshWrapper* square3 = new MeshWrapper(shapes::CreateSquare("square3", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[0][2] = square3;

        MeshWrapper* square4 = new MeshWrapper(shapes::CreateSquare("square4", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[1][0] = square4;

        MeshWrapper* square5 = new MeshWrapper(shapes::CreateSquare("square5", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[1][1] = square5;

        MeshWrapper* square6 = new MeshWrapper(shapes::CreateSquare("square6", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[1][2] = square6;

        MeshWrapper* square7 = new MeshWrapper(shapes::CreateSquare("square7", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[2][0] = square7;

        MeshWrapper* square8 = new MeshWrapper(shapes::CreateSquare("square8", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[2][1] = square8;

        MeshWrapper* square9 = new MeshWrapper(shapes::CreateSquare("square9", corner_, (float)squareSide_, glm::vec3(0, 1, 0), true));
        placings_[2][2] = square9;
    }

    void StaticScene::CreateHitBar()
    {
		MeshWrapper* hitBar = new MeshWrapper(shapes::CreateRectangle("hitBar", corner_, HIT_BAR_LENGTH, HIT_BAR_WIDTH, glm::vec3(1, 0, 0), true));
        hitBar->setColor(glm::vec3(1, 0, 0));
        hitBar_ = hitBar;
	}

    void StaticScene::CreateShooters()
    {
        glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.0f);
        MeshWrapper* shooter = new MeshWrapper(shapes::CreateShooter("shooter1", corner_, (float)(squareSide_ * SHOOTER_SCALE), color, true));
        shooter->setColor(color);
		shooters_.push_back(shooter);   

        color = glm::vec3(0.0f, 0.0f, 1.0f);
        shooter = new MeshWrapper(shapes::CreateShooter("shooter2", corner_, (float)(squareSide_ * SHOOTER_SCALE), color, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);

        color = glm::vec3(1.0f, 1.0f, 0.0f);
        shooter = new MeshWrapper(shapes::CreateShooter("shooter3", corner_, (float)(squareSide_ * SHOOTER_SCALE), color, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);

        color = glm::vec3(0.6f, 0.0f, 1.0f);
        shooter = new MeshWrapper(shapes::CreateShooter("shooter4", corner_, (float)(squareSide_ * SHOOTER_SCALE), color, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);

        glm::vec3 colorOutside = glm::vec3(1.0f, 0.85f, 0.5f);
        glm::vec3 colorInside = glm::vec3(1.0f, 1.0f, 0.98f);
        shooter = new MeshWrapper(shapes::CreateSpawner("spawner", corner_, (float)(squareSide_ * SHOOTER_SCALE), colorOutside, colorInside, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);

        colorOutside = glm::vec3(0.1f, 0.5f, 0.5f);
        colorInside = glm::vec3(1.0f, 1.0f, 0.98f);
        shooter = new MeshWrapper(shapes::CreateCannon("cannon", corner_, (float)(squareSide_ * SHOOTER_SCALE), colorOutside, colorInside, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);

        colorOutside = glm::vec3(0.0f, 0.5f, 0.0f);
        colorInside = glm::vec3(1.0f, 0.0f, 0.0f);
        shooter = new MeshWrapper(shapes::CreateEater("eater", corner_, (float)(squareSide_ * SHOOTER_SCALE), colorOutside, colorInside, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);

        colorOutside = glm::vec3(0.7f, 0.7f, 0.9f);
        colorInside = glm::vec3(1.0f, 1.0f, 1.0f);
        shooter = new MeshWrapper(shapes::CreateSnowCannon("snowCannon", corner_, (float)(squareSide_ * SHOOTER_SCALE), colorOutside, colorInside, true));
        shooter->setColor(color);
        shooters_.push_back(shooter);
    }

    void StaticScene::CreateHealthPoints()
    {
        glm::vec3 color = glm::vec3(1, 0, 0);
        MeshWrapper* healthPoint = new MeshWrapper(shapes::CreateHeart("healthPoint1", corner_, (float)(squareSide_ * HEALTH_POINT_SCALE), color, true));
        healthPoint->setColor(color);
        healthPoints_.push_back(healthPoint);

        healthPoint = new MeshWrapper(shapes::CreateHeart("healthPoint2", corner_, (float)(squareSide_ * HEALTH_POINT_SCALE), color, true));
        healthPoint->setColor(color);
        healthPoints_.push_back(healthPoint);

        healthPoint = new MeshWrapper(shapes::CreateHeart("healthPoint3", corner_, (float)(squareSide_ * HEALTH_POINT_SCALE), color, true));
        healthPoint->setColor(color);
        healthPoints_.push_back(healthPoint);
    }

    void StaticScene::CreatePlaceHolders()
    {
        glm::vec3 color = glm::vec3(1, 1, 1);
        MeshWrapper* placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder1", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder2", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder3", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder4", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder5", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder6", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder7", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);

        placeHolder = new MeshWrapper(shapes::CreateSquare("placeHolder8", corner_, (float)squareSide_, color, false));
        placeHolders_.push_back(placeHolder);
    }

    MeshWrapper* StaticScene::getPlacing(int row, int col) const 
    {
        if (row >= 0 && row < PLACINGS_SIZE && col >= 0 && col < PLACINGS_SIZE) {
            return placings_[row][col];
        }
        else {
            return nullptr;
        }
    }

    MeshWrapper* StaticScene::getHitBar() const
    {
        return hitBar_;
    }

    std::vector<MeshWrapper*> StaticScene::getHealthPoints() const
    {
        return healthPoints_;
    }

    std::vector<MeshWrapper*> StaticScene::getShooters() const
    {
        return shooters_;
    }

    std::vector<MeshWrapper*> StaticScene::getPlaceHolders() const
    {
        return placeHolders_;
    }

} // namespace m1
