#pragma once
#include "components/simple_scene.h"
#include "lab_m1/tema1/MeshWrapper.hpp"

class MeshWrapperBullet : public MeshWrapper
{
public:
	MeshWrapperBullet(Mesh* mesh);
	~MeshWrapperBullet();
	void setShooterPower(int shooterPower);
	int getShooterPower() const;
	void setBulletWasShot(bool bulletWasShot);
	bool getBulletWasShot() const;
	void setAngularStep(float angularStep);
	float getAngularStep() const;
	void setBulletHitSomething(bool bulletHitSomething);
	bool getBulletHitSomething() const;
	void setIsRocket(bool isRocket);
	bool getIsRocket() const;
	void setIsSnowball(bool isSnowball);
	bool getIsSnowball() const;

private:
	int shooterPower_ = 0;
	bool bulletWasShot_ = false;
	float angularStep_ = 0;
	bool bulletHitSomething_ = false;
	bool isRocket_ = false;
	bool isSnowball_ = false;
};