#pragma once
#include "components/simple_scene.h"
#include "lab_m1/tema1/MeshWrapper.hpp"
#define DISAPEAR_STEPS 60


class MeshWrapperShooter : public MeshWrapper
{
public:
	MeshWrapperShooter(Mesh* mesh);
	~MeshWrapperShooter();
	void setShooterPower(int shooterPower);
	int getShooterPower() const;
	void setDisappearSteps(int disappearSteps);
	int getDisappearSteps() const;
	void setCostWasPaid(bool costWasPaid);
	bool getCostWasPaid() const;
	void setIsSpawner(bool isSpawner);
	bool getIsSpawner() const;

private:
	int shooterPower_ = 0;
	int disappearSteps_ = DISAPEAR_STEPS;
	bool costWasPaid_ = false;
	bool isSpawner_ = false;
};