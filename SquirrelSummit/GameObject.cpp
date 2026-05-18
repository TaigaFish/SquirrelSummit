#include "GameObject.h"
#include <iostream>
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"
#include "Commons.h"
#include "Texture2D.h"

GameObject::GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int offsetX, int offsetY, int lengthX, int lengthY)
{
	m_renderer = renderer;
	m_position = start_position;
	m_velocity = Vector2D(0, 0);
	gravityStrength = 0;
	m_maxAcceleration = 0;
	m_maxSpeed = 0;
	m_acceleration = Vector2D(0, gravityStrength);
	terminalVelocity = 0;

	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	collisionOffsetX = offsetX;
	collisionOffsetY = offsetY;
	collisionLengthX = lengthX;
	collisionLengthY = lengthY;
	if (collisionLengthX == 0)
	{
		collisionLengthX = m_texture->GetWidth();
	}
	if (collisionLengthY == 0)
	{
		collisionLengthY = m_texture->GetHeight();
	}
}
GameObject::~GameObject()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void GameObject::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}
bool GameObject::Update(float deltaTime, SDL_Event e)
{
	return true;
}

void GameObject::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}
Vector2D GameObject::GetPosition() const
{
	return m_position;
}
Collision2D GameObject::GetCollisionBox()
{
	return Collision2D(Rect2D(m_position.x+collisionOffsetX, m_position.y+collisionOffsetY, (float)collisionLengthX, (float)collisionLengthY), Vector2D((float)collisionOffsetX, (float)collisionOffsetY));
}
void GameObject::SetVelocity(Vector2D new_velocity)
{
	m_velocity = new_velocity;
}
Vector2D GameObject::GetVelocity() const
{
	return m_velocity;
}

void GameObject::SetAcceleration(Vector2D new_acceleration)
{
	m_acceleration = new_acceleration;
}
Vector2D GameObject::GetAcceleration() const
{
	return m_acceleration;
}