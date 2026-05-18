#include "SDL.h"
#include "constants.h"
#include <iostream>
#include "SDL_image.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_error.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_joystick.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_main.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_stdinc.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_timer.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_video.h"
using namespace std;

//global variables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

//function forward declerations
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* argv[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
		g_old_time = SDL_GetTicks(); //set the time
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}

	g_window = SDL_CreateWindow("Squirrel Summit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == nullptr)
	{
		cout << "Window was not created Error: " << SDL_GetError();
		return false;
	}

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer != nullptr)
	{
		//initialise PNG loading
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}

	SDL_JoystickOpen(1);

	return true; //all ran correctly
}

void CloseSDL()
{
	//destroy the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//destroy the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	//delete the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	SDL_Quit();
}

bool Update()
{
	Uint32 new_time = SDL_GetTicks(); //gets the current time

	//event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle events
	switch (e.type)
	{
	case SDL_QUIT: //ends the game when the "X" is pressed
		return true;
		break;
	default:
		break;
	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time; //updates the old time

	return false; //continues the game loop
}

void Render()
{
	//clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);
}