#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/StaticScene.hpp"
#include "lab_m1/tema1/ColorUtils.hpp"

#define TYPES_OF_SHOOTERS 4
#define SCREEN_WIDTH 1280
#define COIN_SPAWN_RATE 3
#define BIG_COIN_SPAWN_RATE 15
#define SPAWNER_LIFE_TIME 10

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
        void CreateActiveShooters();
        void RendDisapearingShooters();
        void RendEnemies();
        void RendShootersCosts();
        void GenerateEnemies();
        void Shoot();
        void DisapearAnimation(float deltaTimeSeconds, MeshWrapper* mesh, float radius);
        void PulsingAnimation(float deltaTimeSeconds, MeshWrapper* mesh, float radius, float threshold, float speed);
        void RendShootingLine();
        void DetectHitBarCollision();
        void DetectBulletEnemyCollision();
        bool LineContainsEnemyOfColor(int line, glm::vec3 color);
        bool LineContainsEnemy(int line);
        void RendDisapearingEnemies();
        void RendStartingCoins();
        void RendActiveShooters();
        void GenerateRandomCoins();
        void RendRandomCoins();
        void DetectShooterEnemyCollision();
        bool SpawnerIsOnTheTable();
        void MakeShootersDisappear();
        void ClearRandomCoins();
        void EatingAnimation(float deltaTimeSeconds, MeshWrapper* mesh, float radius);
        void UpdateEnemiesTimers(float deltaTimeSeconds);
        void UnfreezeEnemies();
        void IncreaseDifficulty();

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
        bool isSimpleShooter = false;
        bool isSpawner = false;
        bool isCannon = false;
        bool isEater = false;
        bool isSnowCannon = false;
        bool holdingShooter = false;
        int releaseRow = -1;
        int releaseCol = -1;
        float currentTimer = 0;
        glm::vec3 holdingShooterColor;
        glm::vec3 releasedShooterColor;
        MeshWrapperShooter* shootersMatrix[PLACINGS_SIZE][PLACINGS_SIZE];
        float timedShooting[PLACINGS_SIZE][PLACINGS_SIZE];
        std::vector<MeshWrapperBullet*> lineBullets[PLACINGS_SIZE];
        std::vector<MeshWrapperEnemy*> lineEnemies[PLACINGS_SIZE];
        std::vector<MeshWrapperEnemy*> disapearingEnemies[PLACINGS_SIZE];
        std::vector<MeshWrapperCoin*> randomCoins;
        float lineEnemyTimer[PLACINGS_SIZE][TYPES_OF_SHOOTERS];
        bool createdShooter[PLACINGS_SIZE][PLACINGS_SIZE] = { false };
        float slowDownTimer = 0;
        float coinSpawnTimer = 0;
        float bigCoinTimer = 0;
        float healthPointSpawnRate = 0;
        float difficultyTimer = 0;
        int nrOfHealthPoints = HEALTH_POINTS_COUNT;
        int nrOfCoins = DEFAULT_COINS_COUNT;
    };
}   // namespace m1
