#include "MeshWrapper.hpp"

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

void MeshWrapper::setTaken(bool taken)
{
	isTaken_ = taken;
}

bool MeshWrapper::getTaken() const
{
	return isTaken_;
}

void MeshWrapper::setPositionX(float positionX)
{
	positionX_ = positionX;
}

float MeshWrapper::getPositionX() const
{
	return positionX_;
}

void MeshWrapper::setPositionY(float positionY)
{
	positionY_ = positionY;
}

float MeshWrapper::getPositionY() const
{
	return positionY_;
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
	isDisapearing_ = disapearing;
}

bool MeshWrapper::getDisapearing() const
{
	return isDisapearing_;
}

void MeshWrapper::setScaleX(float scaleX)
{
	scaleX_ = scaleX;
}

float MeshWrapper::getScaleX() const
{
	return scaleX_;
}

void MeshWrapper::setScaleY(float scaleY)
{
	scaleY_ = scaleY;
}

float MeshWrapper::getScaleY() const
{
	return scaleY_;
}
