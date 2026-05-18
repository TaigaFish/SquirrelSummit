#include "GameScreenLevel3.h"

#include "Collisions.h"
#include "LockedDoor.h"
#include "PressurePlate.h"
#include "Spikes.h"
#include "Box.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel.h"
#include "LoadingZone.h"
#include "Wall.h"

GameScreenLevel3::GameScreenLevel3(SDL_Renderer* renderer) : GameScreenLevel(renderer, "Images/ForestBG.png")
{
	SetUpLevel3();
	current_screen = SCREEN_LEVEL3;
	next_screen = SCREEN_END;
	prev_screen = SCREEN_LEVEL2;
}

GameScreenLevel3::~GameScreenLevel3()
{
	for (int i = 0; i < k_numSpikeTiles; i++)
	{
		delete spikes[i];
	}
	for (int i = 0; i < k_numWallTiles; i++)
	{
		delete walls[i];
	}
	delete box;
	box = nullptr;
	delete plate;
	plate = nullptr;
	delete door;
	door = nullptr;
	delete loading_zone_previous;
	loading_zone_previous = nullptr;
}

void GameScreenLevel3::Render()
{
	GameScreenLevel::Render();
	for (int i = 0; i < k_numWallTiles; i++)
	{
		walls[i]->Render();
	}
	for (int i = 0; i < k_numSpikeTiles; i++)
	{
		spikes[i]->Render();
	}
	loading_zone_previous->Render();
	door->Render();
	plate->Render();
	box->Render();
}

SCREENS GameScreenLevel3::Update(float deltaTime, SDL_Event e)
{
	bool playerOnGround = false;
	for (int i = 0; i < k_numWallTiles; i++)
	{
		if (walls[i]->Update(deltaTime, e, my_character))
		{
			playerOnGround = true;
		}
	}
	for (int i = 0; i < k_numWallTiles; i++)
	{
		walls[i]->Update(deltaTime, e, box);
	}
	if (loading_zone_previous->Update(deltaTime, e))
	{
		return prev_screen;
	}
	if (loading_zone->Update(deltaTime, e))
	{
		return next_screen;
	}
	for (int i = 0; i < k_numSpikeTiles; i++)
	{
		if (spikes[i]->DamageUpdate(deltaTime, e, my_character))
		{
			return current_screen;
		}
	}
	if (Collisions::Instance()->BoxBlock(my_character, box, deltaTime) == COLLISION_DOWN)
	{
		playerOnGround = true;
	}
	//plate->Update(deltaTime, e, my_character);
	plate->Update(deltaTime, e, box);
	door->Update(deltaTime, e);
	my_character->Update(deltaTime, e, playerOnGround);
	box->Update(deltaTime, e, my_character);
	return SCREEN_NONE;
}

bool GameScreenLevel3::SetUpLevel3()
{
	my_character->SetPosition(Vector2D(24, 416));
	my_character->SetVelocity(Vector2D(100, -600));
	loading_zone->SetPosition(Vector2D(384, 0));

	loading_zone_previous = new LoadingZone(m_renderer, "Images/LoadingZone.png", Vector2D(1, 29), my_character);

	door = new LockedDoor(m_renderer, "Images/doorHorizontal.png", Vector2D(384, 32), Vector2D(-32, 0), my_character);
	plate = new PressurePlate(m_renderer, "Images/plate.png", Vector2D(768, 158), door);
	box = new Box(m_renderer, Vector2D(736, 144));

	SetUpWalls();

	int numSpikes = 0;
	int tempNumSpikes = 0;

	for (unsigned int i = 0; i < 5; i++)
	{
		spikes[i + numSpikes] = new Spikes(m_renderer, "Images/Spike.png", Vector2D(i + 11.f, 26.f));
		tempNumSpikes++;
	}
	numSpikes += tempNumSpikes;
	tempNumSpikes = 0;
	for (unsigned int i = 0; i < 5; i++)
	{
		spikes[i + numSpikes] = new Spikes(m_renderer, "Images/Spike.png", Vector2D(i + 34.f, 26.f));
		tempNumSpikes++;
	}
	numSpikes += tempNumSpikes;
	tempNumSpikes = 0;

	for (unsigned int i = 0; i < 5; i++)
	{
		spikes[i + numSpikes] = new Spikes(m_renderer, "Images/Spike.png", Vector2D(i + 11.f, 18.f));
		tempNumSpikes++;
	}
	numSpikes += tempNumSpikes;
	tempNumSpikes = 0;
	for (unsigned int i = 0; i < 5; i++)
	{
		spikes[i + numSpikes] = new Spikes(m_renderer, "Images/Spike.png", Vector2D(i + 34.f, 18.f));
		tempNumSpikes++;
	}
	numSpikes += tempNumSpikes;
	tempNumSpikes = 0;

	for (unsigned int i = 0; i < 5; i++)
	{
		spikes[i + numSpikes] = new Spikes(m_renderer, "Images/Spike.png", Vector2D(i + 11.f, 9.f));
		tempNumSpikes++;
	}
	numSpikes += tempNumSpikes;
	tempNumSpikes = 0;
	for (unsigned int i = 0; i < 5; i++)
	{
		spikes[i + numSpikes] = new Spikes(m_renderer, "Images/Spike.png", Vector2D(i + 34.f, 9.f));
		tempNumSpikes++;
	}
	numSpikes += tempNumSpikes;
	tempNumSpikes = 0;

	return true;
}

void GameScreenLevel3::SetUpWalls()
{
	int numWalls = 0;
	int tempNumWalls = 0;

	//Floor
	for (unsigned int i = 0; i < 46; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 3.f, 27.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.f, 27.f));
	numWalls++;
	for (unsigned int i = 0; i < 47; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(i + 3.f, 28.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 47; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(i + 3.f, 29.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.f, 29.f));
	numWalls++;

	//Floor 1
	for (unsigned int i = 0; i < 44; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 1.f, 19.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Floor 1
	for (unsigned int i = 0; i < 44; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D(i + 7.f, 10.f), 0, 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Left wall
	for (unsigned int i = 0; i < 26; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileCenterRight.png", Vector2D(0.f, i + 3.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.f, 2.f));
	numWalls++;


	//Roof
	for (unsigned int i = 0; i < 23; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 1.f, 2.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 23; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D(i + 26.f, 2.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	walls[numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.f, 2.f));
	numWalls++;
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D((float)i, 0.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(i + 26.f, 0.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D((float)i, 1.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(i + 26.f, 1.f));
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;

	//Right wall
	for (unsigned int i = 0; i < 24; i++)
	{
		walls[i + numWalls] = new Wall(m_renderer, "Images/BarkTileCenterLeft.png", Vector2D(49.f, i + 3.f), 2);
		tempNumWalls++;
	}
	numWalls += tempNumWalls;
	tempNumWalls = 0;
}