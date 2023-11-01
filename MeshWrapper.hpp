#pragma once
#include "components/simple_scene.h"

class MeshWrapper
{
public:
	MeshWrapper(Mesh* mesh);
	~MeshWrapper();
	void setVisibility(bool visibility);
	bool getVisibility() const;
	void setTaken(bool taken);
	bool getTaken() const;
	void setPositionX(float positionX);
	float getPositionX() const;
	void setPositionY(float positionY);
	float getPositionY() const;
	void setColor(glm::vec3 color);
	glm::vec3 getColor() const;
	Mesh* getMesh() const;
	void setDisapearing(bool disapearing);
	bool getDisapearing() const;
	void setScaleX(float scaleX);
	float getScaleX() const;
	void setScaleY(float scaleY);
	float getScaleY() const;

private:
	Mesh* mesh_;
	bool visible_ = true;
	bool isTaken_ = false;
	bool isDisapearing_ = false;
	glm::vec3 color_ = glm::vec3(0, 0, 0);
	float positionX_ = 0;
	float positionY_ = 0;
	float scaleX_ = 1;
	float scaleY_ = 1;
};