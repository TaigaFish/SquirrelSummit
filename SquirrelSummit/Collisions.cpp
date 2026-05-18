#include "Collisions.h"
#include "GameObject.h"

//initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions() {}
Collisions::~Collisions()
{
	m_instance = nullptr;
	delete m_instance;
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Box(GameObject* a, GameObject* b) 
{
	Rect2D rect1 = a->GetCollisionBox().boundaries;
	Rect2D rect2 = b->GetCollisionBox().boundaries;
	if (rect1.x + rect1.width > rect2.x &&
		rect1.x < rect2.x + rect2.width &&
		rect1.y + rect1.height > rect2.y &&
		rect1.y < rect2.y + rect2.height)
	{
		return true;
	}
	return false;
}
CollisionDir Collisions::BoxDir(GameObject* a, GameObject* b, float deltaTime)
{
	Rect2D rect1 = a->GetCollisionBox().boundaries;
	Rect2D rect2 = b->GetCollisionBox().boundaries;
	Vector2D aVelocity = a->GetVelocity();
	Vector2D bVelocity = b->GetVelocity();
	Vector2D aAcceleration = a->GetAcceleration();
	Vector2D bAcceleration = b->GetAcceleration();
	Vector2D aDisplacement = Vector2D((aVelocity.x + aAcceleration.x * deltaTime) * deltaTime, (aVelocity.y + aAcceleration.y * deltaTime) * deltaTime);
	Vector2D bDisplacement = Vector2D((bVelocity.x + bAcceleration.x * deltaTime) * deltaTime, (bVelocity.y + bAcceleration.y * deltaTime) * deltaTime);
	if (rect1.x + rect1.width + aDisplacement.x >= rect2.x + bDisplacement.x && //next frame positions
		rect1.x + rect1.width <= rect2.x && //current frame positions
		rect1.y + rect1.height > rect2.y &&
		rect1.y < rect2.y + rect2.height)
	{
		return COLLISION_RIGHT;
	}
	if (rect1.x + aDisplacement.x <= rect2.x + rect2.width + bDisplacement.x && //next frame positions
		rect1.x >= rect2.x + rect2.width && //current frame positions
		rect1.y + rect1.height > rect2.y &&
		rect1.y < rect2.y + rect2.height)
	{
		return COLLISION_LEFT;
	}
	if (rect1.y + rect1.height + aDisplacement.y >= rect2.y + bDisplacement.y && //next frame positions
		rect1.y + rect1.height <= rect2.y && //current frame positions
		rect1.x + rect1.width > rect2.x &&
		rect1.x < rect2.x + rect2.width)
	{
		return COLLISION_DOWN;
	}
	if (rect1.y + aDisplacement.y <= rect2.y + rect2.height + bDisplacement.y && //next frame positions
		rect1.y >= rect2.y + rect2.height && //current frame positions
		rect1.x + rect1.width > rect2.x &&
		rect1.x < rect2.x + rect2.width)
	{
		return COLLISION_UP;
	}
	return COLLISION_NONE;
}

CollisionDir Collisions::BoxBlock(GameObject* a, GameObject* b, float deltaTime)
{
	CollisionDir collisionDirection = BoxDir(a, b, deltaTime);
	Vector2D aVelocity = a->GetVelocity();
	Vector2D aPosition = a->GetPosition();
	Vector2D bPosition = b->GetPosition();
	Collision2D obj1 = a->GetCollisionBox();
	Collision2D obj2 = b->GetCollisionBox();
	switch (collisionDirection)
	{
	case COLLISION_DOWN:
		if (aVelocity.y > 0)
		{
			a->SetPosition(Vector2D(aPosition.x, bPosition.y + obj2.offset.y - obj1.boundaries.height - obj1.offset.y));
			a->SetVelocity(Vector2D(aVelocity.x, 0));
		}
		break;
	case COLLISION_UP:
		if (aVelocity.y < 0)
		{
			a->SetPosition(Vector2D(aPosition.x, bPosition.y + obj2.boundaries.height + obj2.offset.y - obj1.offset.y));
			a->SetVelocity(Vector2D(aVelocity.x, 0));
		}
		break;
	case COLLISION_RIGHT:
		if (aVelocity.x > 0)
		{
			a->SetPosition(Vector2D(bPosition.x + obj2.offset.x - obj1.boundaries.width - obj1.offset.x, aPosition.y));
			a->SetVelocity(Vector2D(0, aVelocity.y));
		}
		break;
	case COLLISION_LEFT:
		if (aVelocity.x < 0)
		{
			a->SetPosition(Vector2D(bPosition.x + obj2.boundaries.width + obj2.offset.x - obj1.offset.x, aPosition.y));
			a->SetVelocity(Vector2D(0, aVelocity.y));
		}
		break;
	default:
		break;
	}
	return collisionDirection;
}

CollisionDir Collisions::BoxPush(GameObject* a, GameObject* b, float deltaTime)
{
	CollisionDir collisionDirection = BoxDir(a, b, deltaTime);
	Vector2D aVelocity = a->GetVelocity();
	Vector2D bVelocity = b->GetVelocity();
	Vector2D aPosition = a->GetPosition();
	Vector2D bPosition = b->GetPosition();
	Collision2D obj1 = a->GetCollisionBox();
	Collision2D obj2 = b->GetCollisionBox();
	switch (collisionDirection)
	{
	case COLLISION_LEFT:
	case COLLISION_RIGHT:
		b->SetVelocity(Vector2D(80.0f, bVelocity.y));
		break;
	}
	return collisionDirection;
}