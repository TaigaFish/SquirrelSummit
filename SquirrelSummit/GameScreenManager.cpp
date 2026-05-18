#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenHelp.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenLevel3.h"
#include "GameScreenEnd.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	m_previous_screen = SCREEN_NONE;

	ChangeScreen(startScreen); //starts the first screen
}
GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	SCREENS next_screen = m_current_screen->Update(deltaTime, e);
	if (next_screen == SCREEN_NONE)
	{
		return;
	}
	ChangeScreen(next_screen);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	delete m_current_screen;
	GameScreen* tempScreen;
	bool onEvercade = false;
	switch (new_screen)
	{
	case SCREEN_MENU:
		tempScreen = new GameScreenMenu(m_renderer);
		m_current_screen = tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_HELP_EVERCADE:
		onEvercade = true;
	case SCREEN_HELP_WINDOWS:
		tempScreen = new GameScreenHelp(m_renderer, onEvercade);
		m_current_screen = tempScreen;	
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer, m_previous_screen);
		m_current_screen = tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		tempScreen = new GameScreenLevel2(m_renderer, m_previous_screen);
		m_current_screen = tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL3:
		tempScreen = new GameScreenLevel3(m_renderer);
		m_current_screen = tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_END:
		tempScreen = new GameScreenEnd(m_renderer);
		m_current_screen = tempScreen;
		tempScreen = nullptr;
		break;
	default:
		break;
	}
	m_previous_screen = new_screen;
}