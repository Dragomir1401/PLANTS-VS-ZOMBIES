#include "MeshWrapperBullet.hpp"

MeshWrapperBullet::MeshWrapperBullet(Mesh* mesh)
	: MeshWrapper(mesh)
{
}

MeshWrapperBullet::~MeshWrapperBullet()
{
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

void MeshWrapperBullet::setAngularStep(float angularStep)
{
	angularStep_ = angularStep;
}

float MeshWrapperBullet::getAngularStep() const
{
	return angularStep_;
}

void MeshWrapperBullet::setBulletHitSomething(bool bulletHitSomething)
{
	bulletHitSomething_ = bulletHitSomething;
}

bool MeshWrapperBullet::getBulletHitSomething() const
{
	return bulletHitSomething_;
}

void MeshWrapperBullet::setIsRocket(bool isRocket)
{
	isRocket_ = isRocket;
}

bool MeshWrapperBullet::getIsRocket() const
{
	return isRocket_;
}

void MeshWrapperBullet::setIsSnowball(bool isSnowball)
{
	isSnowball_ = isSnowball;
}

bool MeshWrapperBullet::getIsSnowball() const
{
	return isSnowball_;
}
