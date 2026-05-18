#include "GameScreenLevel1.h"
#include "Wall.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, SCREENS last_screen) : GameScreenLevel(renderer, "Images/ForestBG.png")
{
	SetUpLevel1();
	if (last_screen == SCREEN_LEVEL2)
	{
		my_character->SetPosition(Vector2D(760, 16));
	}
	current_screen = SCREEN_LEVEL1;
	next_screen = SCREEN_LEVEL2;
}
GameScreenLevel1::~GameScreenLevel1()
{
	for (int i = 0; i < NUM_WALL_TILES; i++)
	{
		delete walls[i];
	}
}

void GameScreenLevel1::Render()
{
	GameScreenLevel::Render();
	for (int i = 0; i < NUM_WALL_TILES; i++)
	{
		walls[i]->Render();
	}
}
SCREENS GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	bool playerOnGround = false;
	for (int i = 0; i < NUM_WALL_TILES; i++)
	{
		if (walls[i]->Update(deltaTime, e, my_character))
		{
			playerOnGround = true;
		}
	}
	if (loading_zone->Update(deltaTime, e))
	{
		return next_screen;
	}
	my_character->Update(deltaTime, e, playerOnGround); //update character
	return SCREEN_NONE; //continue with this screen
}

bool GameScreenLevel1::SetUpLevel1()
{
	//moves the character and loading zone to their start locations
	my_character->SetPosition(Vector2D(64.0f, 342.0f));
	loading_zone->SetPosition(Vector2D(752.0f, 0.0f));

	for (unsigned int i = 0; i < 46; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D((i + 1.f), 0.0f), 0, 0); //roof
	}
	for (unsigned int i = 46; i < 64; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileCenterRight.png", Vector2D(0.0f, (i - 45.f)), 0, 0); //left wall pt 1
	}
	for (unsigned int i = 64; i < 70; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileCenterRight.png", Vector2D(0.0f, (i - 43.f)), 0, 0); //left wall pt 2
	}
	for (unsigned int i = 70; i < 77; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileCenterLeft.png", Vector2D(49.0f, (i - 69.f)), 2, 0); //right wall pt 1
	}
	for (unsigned int i = 77; i < 96; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileCenterLeft.png", Vector2D(49.0f, (i - 69.f)), 2, 0); //right wall pt 2
	}
	for (unsigned int i = 96; i < 146; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/FloorTileTopMiddle.png", Vector2D((i - 96.f), 27.0f), 0, 2); //floor
	}
	for (unsigned int i = 146; i < 151; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D((i - 145.f), 19.0f), 0, 2); //left platform top
	}
	for (unsigned int i = 151; i < 156; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D((i - 150.f), 20.0f), 0, 0); //left platform bottom
	}
	for (unsigned int i = 156; i < 161; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D((i - 134.f), 13.0f), 0, 2); //middle platform top
	}
	for (unsigned int i = 161; i < 166; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D((i - 139.f), 14.0f), 0, 0); //middle platform bottom
	}
	for (unsigned int i = 166; i < 171; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D((i - 122.f), 7.0f), 0, 2); //right platform top
	}
	for (unsigned int i = 171; i < 176; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileBottomMiddle.png", Vector2D((i - 127.f), 8.0f), 0, 0); //right platform bottom
	}
	walls[176] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.0f, 0.0f));
	walls[177] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.0f, 0.0f));
	for (unsigned int i = 178; i < 180; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.0f, (i - 159.f)));
	}
	for (unsigned int i = 180; i < 182; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.0f, (i - 173.f)));
	}
	for (unsigned int i = 182; i < 232; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/FloorTileMiddle.png", Vector2D((i - 182.f), 28.0f));
	}
	for (unsigned int i = 232; i < NUM_WALL_TILES; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/FloorTileMiddle.png", Vector2D((i - 232.f), 29.0f));
	}

	return true;
}