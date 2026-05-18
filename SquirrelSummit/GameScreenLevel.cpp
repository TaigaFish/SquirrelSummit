#include "GameScreenLevel.h"
#include <iostream>
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"
#include "Character.h"
#include "Commons.h"
#include "GameScreen.h"
#include "LoadingZone.h"
#include "Texture2D.h"

GameScreenLevel::GameScreenLevel(SDL_Renderer* renderer, std::string backgroundPath) : GameScreen(renderer)
{
	SetUpLevel(backgroundPath);
}

GameScreenLevel::~GameScreenLevel() 
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete my_character;
	my_character = nullptr;

	delete loading_zone;
	loading_zone = nullptr;
}

void GameScreenLevel::Render()
{
	//draw background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//render character
	my_character->Render();

	loading_zone->Render();
}

bool GameScreenLevel::SetUpLevel(std::string backgroundPath)
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile(backgroundPath))
	{
		std::cout << "Failed to load background texture" << std::endl;
		return false;
	}

	my_character = new Character(m_renderer, Vector2D(0, 0)); //set up player character

	loading_zone = new LoadingZone(m_renderer, "Images/LoadingZone.png", Vector2D(0, 0), my_character);
	return true;
}