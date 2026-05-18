#include "GameScreenHelp.h"
#include "GameText.h"
#include "Wall.h"
#include "Texture2D.h"
#include "Character.h"
#include <iostream>
#include <ostream>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_pixels.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"
#include "Commons.h"
#include "GameScreen.h"

GameScreenHelp::GameScreenHelp(SDL_Renderer* renderer, bool onEvercade) : GameScreen(renderer)
{
	SetUpHelp();
	next_screen = SCREEN_LEVEL1;
	if (!onEvercade)
	{
		line1 = "Arrow keys to move";
		line2 = "Space to jump";
		return;
	}
	line1 = "D-pad to move";
	line2 = "A or B to jump";
}

GameScreenHelp::~GameScreenHelp()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete helpText1;
	helpText1 = nullptr;
	delete helpText2;
	helpText2 = nullptr;
	delete subText;
	subText = nullptr;
	delete my_character;
	my_character = nullptr;
	for (int i = 0; i < NUM_WALL_TILES; i++)
	{
		delete walls[i];
	}
}

void GameScreenHelp::Render()
{
	//draw background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	for (int i = 0; i < NUM_WALL_TILES; i++)
	{
		walls[i]->Render();
	}

	helpText1->SetColor(SDL_Color{ 0,0,0,255 });
	helpText1->RenderCentered(line1, 400, 160);
	helpText2->SetColor(SDL_Color{ 0,0,0,255 });
	helpText2->RenderCentered(line2, 400, 252);
	subText->SetColor(SDL_Color{ 0,0,0,255 });
	subText->RenderCentered("Press any key to start", 400, 368);

	my_character->Render();
}

SCREENS GameScreenHelp::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_JOYBUTTONDOWN:
	case SDL_KEYDOWN:
		return SCREEN_LEVEL1;
		break;
	default:
		return SCREEN_NONE;
		break;
	}
}

bool GameScreenHelp::SetUpHelp()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/ForestBG.png"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}

	helpText1 = new GameText(m_renderer, "Fonts/arial.ttf", 18);
	helpText2 = new GameText(m_renderer, "Fonts/arial.ttf", 18);
	subText = new GameText(m_renderer, "Fonts/arial.ttf", 18);

	my_character = new Character(m_renderer, Vector2D(24 * 16, 11 * 16 + 6));

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
	walls[176] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.0f, 0.0f)); //Change to diagonal
	walls[177] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.0f, 0.0f)); //Change to diagonal
	for (unsigned int i = 178; i < 180; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(0.0f, (i - 159.f))); //Change to diagonal
	}
	for (unsigned int i = 180; i < 182; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileMiddle.png", Vector2D(49.0f, (i - 173.f))); //Change to diagonal
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