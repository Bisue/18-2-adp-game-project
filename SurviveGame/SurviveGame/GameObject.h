#pragma once
#include "Game2D.h"

namespace jm
{
	class GameObject
	{
	protected:
		//transform
		vec2 position;
		vec2 scaleSize;
		float rotation;

		//collider(circle)
		float bodyRadius;

	public:
		//constructor
		GameObject(const vec2& position = vec2(0, 0), const vec2& scaleSize = vec2(1, 1), const float& rotation = 0.0f)
			: position(position), scaleSize(scaleSize), rotation(rotation)
		{

		}
		GameObject(const vec2& position = vec2(0, 0), const float& bodyRadius = 0.25f)
			: position(position), scaleSize(vec2(1.0f,1.0f)), rotation(0.0f), bodyRadius(bodyRadius)
		{

		}
		//destructor
		virtual ~GameObject()
		{

		}
		//getter, setter
		vec2 getPos() const
		{
			return position;
		}
		void setPos(const vec2& newPosition)
		{
			position = newPosition;
		}
		vec2 getScale() const
		{
			return scaleSize;
		}
		void setScale(const vec2& newScaleSize)
		{
			scaleSize = newScaleSize;
		}
		float getRotation() const
		{
			return rotation;
		}
		void setRotation(const float& newRotation)
		{
			rotation = newRotation;
		}
		float getBodyRadius() const
		{
			return bodyRadius;
		}
		void setBodyRadius(const float& newBodyRadius)
		{
			bodyRadius = newBodyRadius;
		}
		//pure virtual methods
		//virtual void update() = 0;
		virtual void render() const = 0;
	};
}