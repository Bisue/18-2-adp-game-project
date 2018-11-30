#include "GameObject.h"

namespace jm
{
	GameObject::GameObject(const vec2& position, const vec2& scaleSize, const float& rotation)
		: position(position), scaleSize(scaleSize), rotation(rotation)
	{

	}
	GameObject::GameObject(const vec2& position, const float& bodyRadius)
		: position(position), scaleSize(vec2(1.0f, 1.0f)), rotation(0.0f), bodyRadius(bodyRadius)
	{

	}
	GameObject::~GameObject()
	{

	}

	vec2 GameObject::getPos() const
	{
		return position;
	}
	void GameObject::setPos(const vec2& newPosition)
	{
		position = newPosition;
	}
	vec2 GameObject::getScale() const
	{
		return scaleSize;
	}
	void GameObject::setScale(const vec2& newScaleSize)
	{
		scaleSize = newScaleSize;
	}
	float GameObject::getRotation() const
	{
		return rotation;
	}
	void GameObject::setRotation(const float& newRotation)
	{
		rotation = newRotation;
	}
	float GameObject::getBodyRadius() const
	{
		return bodyRadius;
	}
	void GameObject::setBodyRadius(const float& newBodyRadius)
	{
		bodyRadius = newBodyRadius;
	}
}