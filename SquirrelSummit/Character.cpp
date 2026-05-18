#include "Character.h"
#include "Texture2D.h"
#include "InputHandler.h"

Character::Character(SDL_Renderer* renderer, Vector2D startPosition, std::string imagePath, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, startPosition, offsetX, offsetY, lengthX, lengthY)
{
	m_facing_direction = FACING_RIGHT;
	m_maxAcceleration = 800.0f;
	m_maxSpeed = 400.0f; //if a pixel is about a centimeter, squirrels can run at up to 8.88 m/s (20 mph) which is 888.8 cm/s, this speed is too fast for standard gameplay however
	gravityStrength = 980.0f;
	terminalVelocity = 1028.0f; //terminal velocity for a squirrel is about 10.28 m/s
	m_acceleration = Vector2D(0, gravityStrength);

	m_moving_left = false;
	m_moving_right = false;
}
Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_velocity.x == 0)
	{
		if (m_facing_direction == FACING_RIGHT)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
		else
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
		}
	}
	else
	{
		if (m_velocity.x > 0)
		{
			m_texture->Render(m_position, SDL_FLIP_NONE);
		}
		else
		{
			m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
		}
	}
}
bool Character::Update(float deltaTime, SDL_Event e, bool onGround)
{
	Move(deltaTime);
	GetMovement(e, deltaTime, onGround);
	ApplyAcceleration(deltaTime);
	return true;
}

void Character::Move(float deltaTime)
{
	m_position.x += deltaTime * m_velocity.x;
	m_position.y += deltaTime * m_velocity.y;
}

void Character::GetMovement(SDL_Event e, float deltaTime, bool onGround)
{
	switch (InputHandler::Instance()->PollForInput(e))
	{
	case INPUT_DOWN_LEFT:
		m_moving_left = true;
		m_facing_direction = FACING_LEFT;
		break;
	case INPUT_DOWN_RIGHT:
		m_moving_right = true;
		m_facing_direction = FACING_RIGHT;
		break;
	case INPUT_DOWN_JUMP:
		if (onGround)
		{
			m_velocity.y = m_jumpSpeed;
		}
		break;
	case INPUT_UP_LEFT:
		m_moving_left = false;
		break;
	case INPUT_UP_RIGHT:
		m_moving_right = false;
		break;
	}
	if ((m_moving_left && m_moving_right) || !(m_moving_left || m_moving_right))
	{
		if (m_velocity.x > 0)
		{
			m_acceleration.x = -2 * m_maxAcceleration;
		}
		else if (m_velocity.x < 0)
		{
			m_acceleration.x = 2 * m_maxAcceleration;
		}
		if (std::abs(m_velocity.x) < m_maxAcceleration * deltaTime)
		{
			m_acceleration.x = 0;
			m_velocity.x = 0.0f;
		}
	}
	else if (m_moving_left)
	{
		if (m_velocity.x > 0)
		{
			m_acceleration.x = -2 * m_maxAcceleration;
		}
		else
		{
			m_acceleration.x = -m_maxAcceleration;
		}
	}
	else
	{
		if (m_velocity.x < 0)
		{
			m_acceleration.x = 2 * m_maxAcceleration;
		}
		else
		{
			m_acceleration.x =  m_maxAcceleration;
		}
	}

}

void Character::ApplyAcceleration(float deltaTime)
{
	m_velocity.x += m_acceleration.x * deltaTime;
	if (m_velocity.x > m_maxSpeed)
	{
		m_velocity.x = m_maxSpeed;
	}
	else if (m_velocity.x < -m_maxSpeed)
	{
		m_velocity.x = -m_maxSpeed;
	}
	m_velocity.y += m_acceleration.y * deltaTime;
	if (m_velocity.y > terminalVelocity)
	{
		m_velocity.y = terminalVelocity;
	}
}