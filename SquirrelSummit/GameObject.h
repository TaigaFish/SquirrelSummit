#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Commons.h"
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "GameScreen.h"

class Texture2D;
class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int offsetX = 0, int offsetY = 0, int lengthX = 0, int lengthY = 0);
	~GameObject();

	virtual void Render();
	virtual bool Update(float deltaTime, SDL_Event e); //returns false if needs to delete itself, so references to it can deal with it.
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition() const;
	Collision2D GetCollisionBox();
	void SetVelocity(Vector2D new_velocity);
	Vector2D GetVelocity() const;
	void SetAcceleration(Vector2D new_acceleration);
	Vector2D GetAcceleration() const;
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	int collisionOffsetX;
	int collisionOffsetY;
	int collisionLengthX;
	int collisionLengthY;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	float m_maxSpeed;
	float m_maxAcceleration;
	float gravityStrength;
	float terminalVelocity;
};

#endif // !_GAMEOBJECT_H