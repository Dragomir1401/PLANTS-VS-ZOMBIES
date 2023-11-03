#pragma once
#include "components/simple_scene.h"

class MeshWrapperEnemy
{
public:
	MeshWrapperEnemy(Mesh* mesh);
	~MeshWrapperEnemy();
	void setVisibility(bool visibility);
	bool getVisibility() const;
	glm::vec2 getPosition() const;
	void setPosition(float positionX, float positionY);
	void setColor(glm::vec3 color);
	glm::vec3 getColor() const;
	Mesh* getMesh() const;
	void setScale(float scaleX, float scaleY);
	glm::vec2 getScale() const;
	void setShooterPower(int shooterPower);
	int getShooterPower() const;
	void setTranslate(float translateX, float translateY);
	void setTranslate(glm::vec2 translate);
	glm::vec2 getTranslate() const;
	void setAngularStep(float angularStep);
	float getAngularStep() const;
	void setTimeAccumulator(float timeAccumulator);
	float getTimeAccumulator() const;
	glm::vec2 getMovingPosition() const;
	void setMovingPosition(float positionX, float positionY);
	void setMovingPosition(glm::vec2 position);
	void setEnemyStarted(bool enemyStarted);
	bool getEnemyStarted() const;
	void setEnemyHealth(int enemyHealth);
	int getEnemyHealth() const;
	void setEnemySpeed(float enemySpeed);
	float getEnemySpeed() const;

private:
	Mesh* mesh_;
	bool visible_ = true;
	glm::vec3 color_ = glm::vec3(0, 0, 0);
	glm::vec2 position_ = glm::vec2(0, 0);
	glm::vec2 movingPosition_ = glm::vec2(0, 0);
	glm::vec2 scale_ = glm::vec2(1, 1);
	int shooterPower_ = 0;
	int enemyHealth_ = 0;
	float enemySpeed_ = 0;
	bool enemyStarted_ = false;
	glm::vec2 translate_ = glm::vec2(0, 0);
	float angularStep_ = 0;
	float timeAccumulator_ = 0;
};