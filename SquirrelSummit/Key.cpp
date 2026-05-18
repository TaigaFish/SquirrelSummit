#include "Key.h"
#include "LockedDoor.h"
#include "Collisions.h"
#include "Character.h"

Key::Key(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LockedDoor* door, Character* character, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, start_position, offsetX, offsetY, lengthX, lengthY)
{
	this->door = door;
	player = character;
}
Key::~Key()
{
	door = nullptr;
}

bool Key::Update(float deltaTime, SDL_Event e)
{
	if (Collisions::Instance()->Box(player, this))
	{
		UnlockDoor();
		return false;
	}
	return true;
}

void Key::UnlockDoor()
{
	door->isLocked = false;
}