#include "MeshWrapperEnemy.hpp"

MeshWrapperEnemy::MeshWrapperEnemy(Mesh* mesh)
	: MeshWrapper(mesh)
{
}

MeshWrapperEnemy::~MeshWrapperEnemy()
{
}

void MeshWrapperEnemy::setShooterPower(int shooterPower)
{
	shooterPower_ = shooterPower;
}

int MeshWrapperEnemy::getShooterPower() const
{
	return shooterPower_;
}

void MeshWrapperEnemy::setAngularStep(float angularStep)
{
	angularStep_ = angularStep;
}

float MeshWrapperEnemy::getAngularStep() const
{
	return angularStep_;
}

void MeshWrapperEnemy::setEnemyStarted(bool enemyStarted)
{
	enemyStarted_ = enemyStarted;
}

bool MeshWrapperEnemy::getEnemyStarted() const
{
	return enemyStarted_;
}

void MeshWrapperEnemy::setEnemyHealth(int enemyHealth)
{
	enemyHealth_ = enemyHealth;
}

int MeshWrapperEnemy::getEnemyHealth() const
{
	return enemyHealth_;
}

void MeshWrapperEnemy::setEnemySpeed(float enemySpeed)
{
	enemySpeed_ = enemySpeed;
}

float MeshWrapperEnemy::getEnemySpeed() const
{
	return enemySpeed_;
}

void MeshWrapperEnemy::setEnemyIsDead(bool enemyIsDead)
{
	enemyIsDead_ = enemyIsDead;
}

bool MeshWrapperEnemy::getEnemyIsDead() const
{
	return enemyIsDead_;
}

void MeshWrapperEnemy::setIsHealthPoint(bool isHealthPoint)
{
	isHealthPoint_ = isHealthPoint;
}

bool MeshWrapperEnemy::getIsHealthPoint() const
{
	return isHealthPoint_;
}

void MeshWrapperEnemy::setDisappearSteps(int disappearSteps)
{
	dissapearSteps_ = disappearSteps;
}

int MeshWrapperEnemy::getDisappearSteps() const
{
	return dissapearSteps_;
}


