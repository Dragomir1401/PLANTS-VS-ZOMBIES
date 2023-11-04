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
