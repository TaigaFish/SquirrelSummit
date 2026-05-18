#include "Box.h"
#include "Collisions.h"
#include <cstdlib>
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameObject.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"

Box::Box(SDL_Renderer* renderer, Vector2D startLocation, std::string imagePath, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, startLocation, offsetX, offsetY, lengthX, lengthY)
{
	m_acceleration = Vector2D(-50, 0);
}

Box::~Box() {}

bool Box::Update(float deltaTime, SDL_Event e, GameObject* other)
{
	m_velocity.x += m_acceleration.x * deltaTime;
	if (m_velocity.x > 0)
	{
		m_acceleration = Vector2D(-50, 0);
	}
	else if (m_velocity.x < 0)
	{
		m_acceleration = Vector2D(50, 0);
	}
	if (std::abs(m_velocity.x) < std::abs(m_acceleration.x))
	{
		m_velocity.x = 0;
	}
	m_position.x += m_velocity.x * deltaTime;
	Collisions::Instance()->BoxPush(other, this, deltaTime);
	return true;
}
