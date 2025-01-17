#pragma once
#include "components/simple_scene.h"
#include "lab_m1/tema1/MeshWrapper.hpp"


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
	void setIsCannon(bool isCannon);
	bool getIsCannon() const;
	void setBulletCount(int bulletCount);
	int getBulletCount() const;
	void setIsEater(bool isEater);
	bool getIsEater() const;
	void setEatenCount(int eatenCount);
	int getEatenCount() const;
	void setIsSnowCannon(bool isSnowCannon);
	bool getIsSnowCannon() const;

private:
	int shooterPower_ = 0;
	int disappearSteps_ = DISAPEAR_STEPS;
	bool costWasPaid_ = false;
	bool isSpawner_ = false;
	bool isCannon_ = false;
	bool isEater_ = false;
	bool isSnowCannon_ = false;
	int bulletCount_ = 0;
	int eatenCount_ = 0;
};