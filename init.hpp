#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/StaticScene.hpp"

#define DISAPEAR_STEPS 120
#define TYPES_OF_SHOOTERS 4

namespace m1
{
    class InitClass : public gfxc::SimpleScene
    {
    public:
        InitClass();
        ~InitClass();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;

        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

        void RendPlacings();
        void RendShooters();
        void RendHitBar();
        void RendHealthPoints();
        void RendPlaceHolders();
        void RendMovingShooter();
        void RendActiveShooters();
        void RendDisapearingShooters();
        void Shoot();
        void DisapearAnimation(float deltaTimeSeconds, MeshWrapper* mesh, int displacementScale);
        glm::vec3 SelectColor(int index);
        int SelectShootingPowerByColor(glm::vec3 color);
        void RendShootingLine();
        int GetTypeByColor(glm::vec3 color);
        int GetBulletIntervalByColor(glm::vec3 color);


    protected:
        double cx, cy;
        glm::mat3 modelMatrix;
        double translateX, translateY;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float angularStep;
        m1::StaticScene *staticScene;
        bool pressedCorrectly = false;
        bool releasedCorrectly = false;
        bool holdingShooter = false;
        int releaseRow = -1;
        int releaseCol = -1;
        float currentTimer = 0;
        glm::vec3 holdingShooterColor;
        glm::vec3 releasedShooterColor;
        MeshWrapper* shootersMatrix[PLACINGS_SIZE][PLACINGS_SIZE];
        float timedShooting[PLACINGS_SIZE][PLACINGS_SIZE];
        int disapearSteps = DISAPEAR_STEPS;
        std::vector<MeshWrapper*> line1Bullets;
    };
}   // namespace m1
