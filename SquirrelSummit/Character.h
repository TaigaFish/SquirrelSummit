#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(SDL_Renderer* renderer, Vector2D startPosition, std::string imagePath ="Images/SquirrelCharacter.png", int offsetX = 0, int offsetY = 4, int lengthX = 16, int lengthY = 22);
	~Character();

	virtual void Render() override;
	virtual bool Update(float deltaTime, SDL_Event e, bool onGround);
protected:
	bool m_moving_left;
	bool m_moving_right;
	float m_jumpSpeed = -627;

	virtual void Move(float deltaTime);
private:
	FACING m_facing_direction;
	void GetMovement(SDL_Event e, float deltaTime, bool onGround);
	void ApplyAcceleration(float deltaTime);
};

#endif // !_CHARACTER_H