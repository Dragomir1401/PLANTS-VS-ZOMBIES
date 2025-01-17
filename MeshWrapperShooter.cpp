#include "MeshWrapper.hpp"
#include "MeshWrapperShooter.hpp"

MeshWrapperShooter::MeshWrapperShooter(Mesh* mesh)
	: MeshWrapper(mesh)
{
}

MeshWrapperShooter::~MeshWrapperShooter()
{
}

void MeshWrapperShooter::setShooterPower(int shooterPower)
{
	shooterPower_ = shooterPower;
}

int MeshWrapperShooter::getShooterPower() const
{
	return shooterPower_;
}

void MeshWrapperShooter::setDisappearSteps(int disappearSteps)
{
	disappearSteps_ = disappearSteps;
}

int MeshWrapperShooter::getDisappearSteps() const
{
	return disappearSteps_;
}

void MeshWrapperShooter::setCostWasPaid(bool costWasPaid)
{
	costWasPaid_ = costWasPaid;
}

bool MeshWrapperShooter::getCostWasPaid() const
{
	return costWasPaid_;
}

void MeshWrapperShooter::setIsSpawner(bool isSpawner)
{
	isSpawner_ = isSpawner;
}

bool MeshWrapperShooter::getIsSpawner() const
{
	return isSpawner_;	
}

void MeshWrapperShooter::setIsCannon(bool isCannon)
{
	isCannon_ = isCannon;
}

bool MeshWrapperShooter::getIsCannon() const
{
	return isCannon_;
}

void MeshWrapperShooter::setBulletCount(int bulletCount)
{
	bulletCount_ = bulletCount;
}

int MeshWrapperShooter::getBulletCount() const
{
	return bulletCount_;
}

void MeshWrapperShooter::setIsEater(bool isEater)
{
	isEater_ = isEater;
}

bool MeshWrapperShooter::getIsEater() const
{
	return isEater_;
}

void MeshWrapperShooter::setEatenCount(int eatenCount)
{
	eatenCount_ = eatenCount;
}

int MeshWrapperShooter::getEatenCount() const
{
	return eatenCount_;
}

void MeshWrapperShooter::setIsSnowCannon(bool isSnowCannon)
{
	isSnowCannon_ = isSnowCannon;
}

bool MeshWrapperShooter::getIsSnowCannon() const
{
	return isSnowCannon_;
}