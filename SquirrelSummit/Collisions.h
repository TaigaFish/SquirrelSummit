#pragma once
#include "Commons.h"

class GameObject;
class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	//bool Circle(GameObject* a, GameObject* b);
	bool Box(GameObject* a, GameObject* b);
	CollisionDir BoxDir(GameObject* a, GameObject* b, float deltaTime);
	CollisionDir BoxBlock(GameObject* a, GameObject* b, float deltaTime);
	CollisionDir BoxPush(GameObject* a, GameObject* b, float deltaTime);
private:
	Collisions();

	static Collisions* m_instance;
};

