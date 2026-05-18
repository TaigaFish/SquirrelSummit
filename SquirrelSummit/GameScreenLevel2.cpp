#include "GameScreenLevel2.h"
#include "Wall.h"
#include "LockedDoor.h"
#include "Key.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel.h"
#include "LoadingZone.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, SCREENS lastScreen) : GameScreenLevel(renderer, "Images/ForestBG.png")
{
	SetUpLevel2();
	if (lastScreen == SCREEN_LEVEL3)
	{
		my_character->SetPosition(Vector2D(24, 16));
		my_character->SetVelocity(Vector2D(0, 0));
		door->isLocked = false;
		delete key;
		key = nullptr;
	}
	current_screen = SCREEN_LEVEL2;
	next_screen = SCREEN_LEVEL3;
	prev_screen = SCREEN_LEVEL1;
}
GameScreenLevel2::~GameScreenLevel2() 
{
	for (int i = 0; i < k_numWallTiles; i++)
	{
		delete walls[i];
	}
	delete door;
	door = nullptr;
	delete key;
	key = nullptr;
	delete loading_zone_previous;
	loading_zone_previous = nullptr;
}

void GameScreenLevel2::Render()
{
	GameScreenLevel::Render();
	loading_zone_previous->Render();

	for (int i = 0; i < k_numWallTiles; i++)
	{
		walls[i]->Render();
	}

	door->Render();
	if (key != nullptr)
	{
		key->Render();
	}
}
SCREENS GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	bool playerOnGround = false;
	for (int i = 0; i < k_numWallTiles; i++)
	{
		if (walls[i]->Update(deltaTime, e, my_character))
		{
			playerOnGround = true;
		}
	}
	if (key != nullptr)
	{
		if (!key->Update(deltaTime, e))
		{
			delete key;
			key = nullptr;
		}
	}
	if (door->Update(deltaTime, e))
	{
		playerOnGround = true;
	}

	if (loading_zone_previous->Update(deltaTime, e))
	{
		return prev_screen;
	}

	if (loading_zone->Update(deltaTime,e))
	{
		return next_screen;
	}

	my_character->Update(deltaTime, e, playerOnGround); //update character
	return SCREEN_NONE; //continue with level
}

bool GameScreenLevel2::SetUpLevel2()
{
	my_character->SetPosition(Vector2D(760.f, 416.f));
	my_character->SetVelocity(Vector2D(-100.f, -600.f));
	loading_zone->SetPosition(Vector2D(16.f, 0.f));

	loading_zone_previous = new LoadingZone(m_renderer, "Images/LoadingZone.png", Vector2D(47.f, 29.f), my_character);

	door = new LockedDoor(m_renderer, "Images/door.png", Vector2D(392.f, 400.f), Vector2D(0.f, -32.f), my_character);
	key = new Key(m_renderer, "Images/key.png", Vector2D(736.f, 64.f), door, my_character);

	int numWalls = 0;
	int tempNumWalls = 0;

	//Bottom Platform, right side
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 26.f, 20.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 26.f, 21.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Middle Platform, right side
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 35.f, 12.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 35.f, 13.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Top Platform, right side
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 45.f, 6.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 45.f, 7.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Bottom Platform, left side
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 20.f, 20.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 20.f, 21.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Middle Platform, left side
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 12.f, 12.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 12.f, 13.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Top Platform, left side
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 1.f, 6.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 1.f, 7.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Left wall
	for (unsigned int i = 0; i < 27; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileCenterRight.png", Vector2D(0.f, (float)i));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Middle wall
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i+numWalls] = new Wall(m_renderer, "Images/BarkTileCenterLeft.png", Vector2D(24.f, i + 1.f), 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i+numWalls] = new Wall(m_renderer, "Images/BarkTileCenterRight.png", Vector2D(25.f, i + 1.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Floor
	for (unsigned int i = 0; i < 46; i++)
	{
		walls[i+numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 1.f, 27.0f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 47; i++)
	{
		walls[i+numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D((float)i, 28.0f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 47; i++)
	{
		walls[i+numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D((float)i, 29.0f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Right wall
	for (unsigned int i = 0; i < 29; i++)
	{
		walls[i+numWalls] = new Wall(m_renderer, "Images/BarkTileCenterLeft.png", Vector2D(49.f, i + 1.f), 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Top wall
	for (unsigned int i = 0; i < 21; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 3.f, 0.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 23; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 26.f, 0.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(24.f, 0.f));
	numWalls++;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(25.f, 0.f));
	numWalls++;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.f, 0.f));
	numWalls++;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.f, 27.f));
	numWalls++;
	
	return true;
}