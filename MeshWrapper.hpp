#pragma once
#include "components/simple_scene.h"
#define DISAPEAR_STEPS 60


class MeshWrapper
{
public:
	MeshWrapper();
	MeshWrapper(Mesh* mesh);
	~MeshWrapper();
	void setVisibility(bool visibility);
	bool getVisibility() const;
	void setColor(glm::vec3 color);
	glm::vec3 getColor() const;
	Mesh* getMesh() const;
	void setDisapearing(bool disapearing);
	bool getDisapearing() const;
	void setTimeAccumulator(float timeAccumulator);
	float getTimeAccumulator() const;
	glm::vec2 getPosition() const;
	void setPosition(float positionX, float positionY);
	void setPosition(glm::vec2 position);
	void setScale(float scaleX, float scaleY);
	void setScale(glm::vec2 scale);
	glm::vec2 getScale() const;
	void setMovingPosition(float positionX, float positionY);
	void setMovingPosition(glm::vec2 position);
	glm::vec2 getMovingPosition() const;
	void setTranslate(float translateX, float translateY);
	void setTranslate(glm::vec2 translate);
	glm::vec2 getTranslate() const;
	void setTaken(bool taken);
	bool getTaken() const;
	void setAngularStep(float angularStep);
	float getAngularStep() const;
	void setFrozenPosition(float positionX, float positionY);
	void setFrozenPosition(glm::vec2 position);
	glm::vec2 getFrozenPosition() const;

protected:
	Mesh* mesh_;
	bool visible_ = true;
	glm::vec3 color_ = glm::vec3(0, 0, 0);
	glm::vec2 position_ = glm::vec2(0, 0);
	glm::vec2 frozenPosition_ = glm::vec2(0, 0);
	glm::vec2 movingPosition_ = glm::vec2(0, 0);
	glm::vec2 scale_ = glm::vec2(1, 1);
	glm::vec2 translate_ = glm::vec2(0, 0);
	float angularStep_ = 0;
	float timeAccumulator_ = 0;
	bool disapearing_ = false;
	bool taken_ = false;
};