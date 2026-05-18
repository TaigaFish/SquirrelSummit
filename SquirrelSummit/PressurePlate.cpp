#include "PressurePlate.h"
#include "LockedDoor.h"
#include "Collisions.h"

PressurePlate::PressurePlate(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LockedDoor* door, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, start_position, offsetX, offsetY, lengthX, lengthY)
{
	this->door = door;
}
PressurePlate::~PressurePlate()
{
	door = nullptr;
}

bool PressurePlate::Update(float deltaTime, SDL_Event e, GameObject* other)
{
	if (Collisions::Instance()->Box(this, other))
	{
		UnlockDoor();
	}
	else
	{
		LockDoor();
	}
	return true;
}

void PressurePlate::UnlockDoor()
{
	door->isLocked = false;
}
void PressurePlate::LockDoor()
{
	door->isLocked = true;
}