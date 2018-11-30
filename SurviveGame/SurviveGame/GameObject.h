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
		GameObject(const vec2& position = vec2(0, 0), const vec2& scaleSize = vec2(1, 1), const float& rotation = 0.0f);
		GameObject(const vec2& position = vec2(0, 0), const float& bodyRadius = 0.25f);
		//destructor
		virtual ~GameObject();

		//getter, setter
		vec2 getPos() const;
		void setPos(const vec2& newPosition);
		vec2 getScale() const;
		void setScale(const vec2& newScaleSize);
		float getRotation() const;
		void setRotation(const float& newRotation);
		float getBodyRadius() const;
		void setBodyRadius(const float& newBodyRadius);

		//pure virtual methods;
		virtual void render() const = 0;
	};
}