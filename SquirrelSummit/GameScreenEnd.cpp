#include "GameScreenEnd.h"

#include "Character.h"
#include "GameText.h"
#include "Wall.h"
#include "Texture2D.h"
#include <iostream>
#include <ostream>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_pixels.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"
#include "Commons.h"
#include "GameScreen.h"

GameScreenEnd::GameScreenEnd(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpEnd();
}

GameScreenEnd::~GameScreenEnd()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	for (int i = 0; i < k_numWallTiles; i++)
	{
		delete walls[i];
	}
	delete endTextLine1;
	endTextLine1 = nullptr;
	delete endTextLine2;
	endTextLine2 = nullptr;
	delete my_character;
	my_character = nullptr;
}

void GameScreenEnd::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	for (int i = 0; i < k_numWallTiles; i++)
	{
		walls[i]->Render();
	}
	my_character->Render();
	endTextLine1->SetColor(SDL_Color{ 0,0,0,255 });
	endTextLine1->RenderCentered("You reached the top!", 400, 160);
	endTextLine2->SetColor(SDL_Color{ 0,0,0,255 });
	endTextLine2->RenderCentered("Thanks for playing my game!", 400, 240);
}

void GameScreenEnd::SetUpEnd()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/ForestBG.png"))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return;
	}
	endTextLine1 = new GameText(m_renderer, "Fonts/arial.ttf", 48);
	endTextLine2 = new GameText(m_renderer, "Fonts/arial.ttf", 32);
	my_character = new Character(m_renderer, Vector2D(392, 440));

	for (unsigned int i = 0; i < k_numWallTiles; i++)
	{
		walls[i] = new Wall(m_renderer, "Images/BarkTileTopMiddle.png", Vector2D((float)i, 29.f));
	}
}