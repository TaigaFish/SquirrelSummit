#include "LockedDoor.h"

#include "Collisions.h"
#include "Character.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameObject.h"
#include "GameScreen.h"

LockedDoor::LockedDoor(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Vector2D end_offset, Character* character, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, start_position, offsetX, offsetY, lengthX, lengthY)
{
	player = character;

	startPosition = start_position;
	endPosition.x = start_position.x + end_offset.x;
	endPosition.y = start_position.y + end_offset.y;
	m_maxAcceleration = 180.0f;
	m_maxSpeed = 60.0f;
	float offsetLength = sqrtf((end_offset.x * end_offset.x) + (end_offset.y * end_offset.y));
	m_acceleration.x = std::abs(end_offset.x / offsetLength) * m_maxAcceleration;
	m_acceleration.y = std::abs(end_offset.y / offsetLength) * m_maxAcceleration;
	m_maxVelocity.x = std::abs(end_offset.x / offsetLength) * m_maxSpeed;
	m_maxVelocity.y = std::abs(end_offset.y / offsetLength) * m_maxSpeed;
}
LockedDoor::~LockedDoor(){}

bool LockedDoor::Update(float deltaTime, SDL_Event e)
{
	if (isLocked)
	{
		if (isOpening)
		{
			m_velocity.x = 0;
			m_velocity.y = 0;
			isOpening = false;
		}
		isClosing = !Close(deltaTime);
		if (!isClosing)
		{
			m_velocity.x = 0;
			m_velocity.y = 0;
		}
	}
	else
	{
		if (isClosing)
		{
			m_velocity.x = 0;
			m_velocity.y = 0;
			isClosing = false;
		}
		isOpening = !Open(deltaTime);
		if (!isOpening)
		{
			m_velocity.x = 0;
			m_velocity.y = 0;
		}
	}
	if (Collisions::Instance()->BoxBlock(player, this, deltaTime) == COLLISION_DOWN)
	{
		return true;
	}
	return false;
}
bool LockedDoor::Open(float deltaTime)
{
	return Move(deltaTime, startPosition, endPosition);
}
bool LockedDoor::Close(float deltaTime)
{
	return Move(deltaTime, endPosition, startPosition);
}
bool LockedDoor::Move(float deltaTime, Vector2D startPos, Vector2D endPos)
{
	bool movingOnPosX = endPos.x > startPos.x;
	bool movingOnPosY = endPos.y > startPos.y;

	//add x acceleration
	if (movingOnPosX)
	{
		m_velocity.x += m_acceleration.x * deltaTime;
	}
	else
	{
		m_velocity.x -= m_acceleration.x * deltaTime;
	}
	//add y acceleration
	if (movingOnPosY)
	{
		m_velocity.y += m_acceleration.y * deltaTime;
	}
	else
	{
		m_velocity.y -= m_acceleration.y * deltaTime;
	}

	//check x velocity
	if ((m_velocity.x > m_maxVelocity.x) && movingOnPosX)
	{
		m_velocity.x = m_maxVelocity.x;
	}
	else if ((m_velocity.x < -m_maxVelocity.x) && !movingOnPosX)
	{
		m_velocity.x = -m_maxVelocity.x;
	}
	//check y velocity
	if ((m_velocity.y > m_maxVelocity.y) && movingOnPosY)
	{
		m_velocity.y = m_maxVelocity.y;
	}
	else if ((m_velocity.y < -m_maxVelocity.y) && !movingOnPosY)
	{
		m_velocity.y = -m_maxVelocity.y;
	}

	m_position.x += m_velocity.x * deltaTime;
	m_position.y += m_velocity.y * deltaTime;

	if (((m_position.x > endPos.x) && movingOnPosX) || ((m_position.x < endPos.x) && !movingOnPosX))
	{
		m_position.x = endPos.x;
	}
	if (((m_position.y > endPos.y) && movingOnPosY) || ((m_position.y < endPos.y) && !movingOnPosY))
	{
		m_position.y = endPos.y;
	}
	return (m_position.x == endPos.x) && (m_position.y == endPos.y);
}