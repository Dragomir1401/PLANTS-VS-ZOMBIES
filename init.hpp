#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/StaticScene.hpp"
#include "lab_m1/tema1/ColorUtils.hpp"

#define DISAPEAR_STEPS 120
#define TYPES_OF_SHOOTERS 4
#define SCREEN_WIDTH 1280

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
        void RendEnemies();
        void GenerateEnemies();
        void Shoot();
        void DisapearAnimation(float deltaTimeSeconds, MeshWrapper* mesh, int displacementScale);
        void RendShootingLine();

    protected:
        double cx, cy;
        glm::mat3 modelMatrix;
        double translateX, translateY;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float angularStep;
        m1::StaticScene *staticScene;
        m1::ColorUtils *colorUtils;
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
        std::vector<MeshWrapperBullet*> lineBullets[PLACINGS_SIZE];
        std::vector<MeshWrapperEnemy*> lineEnemies[PLACINGS_SIZE];
        float lineEnemyTimer[PLACINGS_SIZE][TYPES_OF_SHOOTERS];

    };
}   // namespace m1
