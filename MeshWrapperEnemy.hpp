#pragma once
#include "components/simple_scene.h"
#include "lab_m1/tema1/MeshWrapper.hpp"
#define DISAPEAR_STEPS 60

class MeshWrapperEnemy : public MeshWrapper
{
public:
	MeshWrapperEnemy(Mesh* mesh);
	~MeshWrapperEnemy();
	void setShooterPower(int shooterPower);
	int getShooterPower() const;
	void setAngularStep(float angularStep);
	float getAngularStep() const;
	void setEnemyStarted(bool enemyStarted);
	bool getEnemyStarted() const;
	void setEnemyHealth(int enemyHealth);
	int getEnemyHealth() const;
	void setEnemySpeed(float enemySpeed);
	float getEnemySpeed() const;
	void setEnemyIsDead(bool enemyIsDead);
	bool getEnemyIsDead() const;
	void setIsHealthPoint(bool isHealthPoint);
	bool getIsHealthPoint() const;
	void setDisappearSteps(int disappearSteps);
	int getDisappearSteps() const;
	void setIsFrozen(bool isFrozen);
	bool getIsFrozen() const;

private:
	int shooterPower_ = 0;
	int enemyHealth_ = 0;
	float enemySpeed_ = 0;
	bool enemyStarted_ = false;
	float angularStep_ = 0;
	bool enemyIsDead_ = false;
	bool isHealthPoint_ = false;
	int dissapearSteps_ = DISAPEAR_STEPS;
	bool isFrozen_ = false;
};