#include "MeshWrapperEnemy.hpp"

MeshWrapperEnemy::MeshWrapperEnemy(Mesh* mesh)
{
	mesh_ = mesh;
}

MeshWrapperEnemy::~MeshWrapperEnemy()
{
}

void MeshWrapperEnemy::setVisibility(bool visibility)
{
	visible_ = visibility;
}

bool MeshWrapperEnemy::getVisibility() const
{
	return visible_;
}

void MeshWrapperEnemy::setPosition(float positionX, float positionY)
{
	position_ = glm::vec2(positionX, positionY);
}

glm::vec2 MeshWrapperEnemy::getPosition() const
{
	return position_;
}

void MeshWrapperEnemy::setColor(glm::vec3 color)
{
	color_ = color;
}

glm::vec3 MeshWrapperEnemy::getColor() const
{
	return color_;
}

Mesh* MeshWrapperEnemy::getMesh() const
{
	return mesh_;
}

void MeshWrapperEnemy::setScale(float scaleX, float scaleY)
{
	scale_ = glm::vec2(scaleX, scaleY);
}

glm::vec2 MeshWrapperEnemy::getScale() const
{
	return scale_;
}

void MeshWrapperEnemy::setShooterPower(int shooterPower)
{
	shooterPower_ = shooterPower;
}

int MeshWrapperEnemy::getShooterPower() const
{
	return shooterPower_;
}

void MeshWrapperEnemy::setTranslate(float translateX, float translateY)
{
	translate_ = glm::vec2(translateX, translateY);
}

void MeshWrapperEnemy::setTranslate(glm::vec2 translate)
{
	translate_ = translate;
}

glm::vec2 MeshWrapperEnemy::getTranslate() const
{
	return translate_;
}

void MeshWrapperEnemy::setAngularStep(float angularStep)
{
	angularStep_ = angularStep;
}

float MeshWrapperEnemy::getAngularStep() const
{
	return angularStep_;
}

void MeshWrapperEnemy::setTimeAccumulator(float timeAccumulator)
{
	timeAccumulator_ = timeAccumulator;
}

float MeshWrapperEnemy::getTimeAccumulator() const
{
	return timeAccumulator_;
}

glm::vec2 MeshWrapperEnemy::getMovingPosition() const
{
	return movingPosition_;
}

void MeshWrapperEnemy::setMovingPosition(float positionX, float positionY)
{
	movingPosition_ = glm::vec2(positionX, positionY);
}

void MeshWrapperEnemy::setMovingPosition(glm::vec2 position)
{
	movingPosition_ = position;
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

void MeshWrapperEnemy::setEnemySpeed(int enemySpeed)
{
	enemySpeed_ = enemySpeed;
}

int MeshWrapperEnemy::getEnemySpeed() const
{
	return enemySpeed_;
}


