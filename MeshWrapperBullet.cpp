#include "MeshWrapperBullet.hpp"

MeshWrapperBullet::MeshWrapperBullet(Mesh* mesh)
{
	mesh_ = mesh;
}

MeshWrapperBullet::~MeshWrapperBullet()
{
}

void MeshWrapperBullet::setVisibility(bool visibility)
{
	visible_ = visibility;
}

bool MeshWrapperBullet::getVisibility() const
{
	return visible_;
}

void MeshWrapperBullet::setPosition(float positionX, float positionY)
{
	position_ = glm::vec2(positionX, positionY);
}

glm::vec2 MeshWrapperBullet::getPosition() const
{
	return position_;
}

void MeshWrapperBullet::setColor(glm::vec3 color)
{
	color_ = color;
}

glm::vec3 MeshWrapperBullet::getColor() const
{
	return color_;
}

Mesh* MeshWrapperBullet::getMesh() const
{
	return mesh_;
}

void MeshWrapperBullet::setScale(float scaleX, float scaleY)
{
	scale_ = glm::vec2(scaleX, scaleY);
}

glm::vec2 MeshWrapperBullet::getScale() const
{
	return scale_;
}

void MeshWrapperBullet::setShooterPower(int shooterPower)
{
	shooterPower_ = shooterPower;
}

int MeshWrapperBullet::getShooterPower() const
{
	return shooterPower_;
}

void MeshWrapperBullet::setBulletWasShot(bool bulletWasShot)
{
	bulletWasShot_ = bulletWasShot;
}

bool MeshWrapperBullet::getBulletWasShot() const
{
	return bulletWasShot_;
}

void MeshWrapperBullet::setTranslate(float translateX, float translateY)
{
	translate_ = glm::vec2(translateX, translateY);
}

void MeshWrapperBullet::setTranslate(glm::vec2 translate)
{
	translate_ = translate;
}

glm::vec2 MeshWrapperBullet::getTranslate() const
{
	return translate_;
}

void MeshWrapperBullet::setAngularStep(float angularStep)
{
	angularStep_ = angularStep;
}

float MeshWrapperBullet::getAngularStep() const
{
	return angularStep_;
}

void MeshWrapperBullet::setTimeAccumulator(float timeAccumulator)
{
	timeAccumulator_ = timeAccumulator;
}

float MeshWrapperBullet::getTimeAccumulator() const
{
	return timeAccumulator_;
}

glm::vec2 MeshWrapperBullet::getMovingPosition() const
{
	return movingPosition_;
}

void MeshWrapperBullet::setMovingPosition(float positionX, float positionY)
{
	movingPosition_ = glm::vec2(positionX, positionY);
}

void MeshWrapperBullet::setMovingPosition(glm::vec2 position)
{
	movingPosition_ = position;
}
