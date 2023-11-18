#include "MeshWrapper.hpp"

MeshWrapper::MeshWrapper()
{
	mesh_ = new Mesh("mesh");
}

MeshWrapper::MeshWrapper(Mesh* mesh)
{
	mesh_ = mesh;
}

MeshWrapper::~MeshWrapper()
{
}

void MeshWrapper::setVisibility(bool visibility)
{
	visible_ = visibility;
}

bool MeshWrapper::getVisibility() const
{
	return visible_;
}

void MeshWrapper::setColor(glm::vec3 color)
{
	color_ = color;
}

glm::vec3 MeshWrapper::getColor() const
{
	return color_;
}

Mesh* MeshWrapper::getMesh() const
{
	return mesh_;
}

void MeshWrapper::setDisapearing(bool disapearing)
{
	disapearing_ = disapearing;
}

bool MeshWrapper::getDisapearing() const
{
	return disapearing_;
}

void MeshWrapper::setTimeAccumulator(float timeAccumulator)
{
	timeAccumulator_ = timeAccumulator;
}

float MeshWrapper::getTimeAccumulator() const
{
	return timeAccumulator_;
}

glm::vec2 MeshWrapper::getPosition() const
{
	return position_;
}

void MeshWrapper::setPosition(float positionX, float positionY)
{
	position_ = glm::vec2(positionX, positionY);
}

void MeshWrapper::setPosition(glm::vec2 position)
{
	position_ = position;
}

void MeshWrapper::setScale(float scaleX, float scaleY)
{
	scale_ = glm::vec2(scaleX, scaleY);
}

void MeshWrapper::setScale(glm::vec2 scale)
{
	scale_ = scale;
}

glm::vec2 MeshWrapper::getScale() const
{
	return scale_;
}

void MeshWrapper::setMovingPosition(float positionX, float positionY)
{
	movingPosition_ = glm::vec2(positionX, positionY);
}

void MeshWrapper::setMovingPosition(glm::vec2 position)
{
	movingPosition_ = position;
}

glm::vec2 MeshWrapper::getMovingPosition() const
{
	return movingPosition_;
}

void MeshWrapper::setTranslate(float translateX, float translateY)
{
	translate_ = glm::vec2(translateX, translateY);
}

void MeshWrapper::setTranslate(glm::vec2 translate)
{
	translate_ = translate;
}

glm::vec2 MeshWrapper::getTranslate() const
{
	return translate_;
}

void MeshWrapper::setTaken(bool taken)
{
	taken_ = taken;
}

bool MeshWrapper::getTaken() const
{
	return taken_;
}

void MeshWrapper::setAngularStep(float angularStep)
{
	angularStep_ = angularStep;
}

float MeshWrapper::getAngularStep() const
{
	return angularStep_;
}

void MeshWrapper::setFrozenPosition(float positionX, float positionY)
{
	frozenPosition_ = glm::vec2(positionX, positionY);
}

void MeshWrapper::setFrozenPosition(glm::vec2 position)
{
	frozenPosition_ = position;
}

glm::vec2 MeshWrapper::getFrozenPosition() const
{
	return frozenPosition_;
}

void MeshWrapper::setType(int type)
{
	type_ = type;
}

int MeshWrapper::getType() const
{
	return type_;
}
