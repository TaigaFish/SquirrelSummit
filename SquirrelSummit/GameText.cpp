#include "GameText.h"

bool GameText::ttfHasInit = false;

GameText::GameText(SDL_Renderer* renderer, const std::string& fontPath, unsigned int fontSize)
{
	if (!InitTTF())
	{
		std::cerr << "Couldn't initialise TTF; error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return;
	}

	this->renderer = renderer;
	this->LoadFont(fontPath, fontSize);
}
GameText::~GameText()
{
	Destroy();
}

bool GameText::LoadFont(const std::string& fontPath, unsigned int fontSize)
{
	this->font = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (!this->font)
	{
		std::cerr << "Couldn't load font from path " << fontPath << "; error is " << TTF_GetError() << std::endl;
		errorEncountered = true;
		return false;
	}
	return true;
}

void GameText::RenderAt(const std::string& text, int x, int y)
{
	int w, h;
	SetupRender(text, w, h);

	Render(x, y, w, h);
}

void GameText::RenderCentered(const std::string& text, int x, int y)
{
	int w, h;
	SetupRender(text, w, h);

	Render(x - w / 2, y, w, h);
}

void GameText::SetColor(SDL_Color color)
{
	this->color = color;
}

void GameText::Destroy(){}

bool GameText::InitTTF()
{
	if (ttfHasInit)
	{
		return true;
	}

	return (TTF_Init() >= 0); //initialises TTF, returning an error if something goes wrong
}

void GameText::SetupRender(const std::string& text, int& w, int& h)
{
	if (errorEncountered)
	{
		return;
	}

	//clears up old texture if neccessary
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}

	TTF_SizeText(font, text.c_str(), &w, &h); //works out the text size from font

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color); //creates surface from text
	texture = SDL_CreateTextureFromSurface(renderer, surface); //creates texture from surface
	SDL_FreeSurface(surface);
}

void GameText::Render(int x, int y, int w, int h)
{
	SDL_Rect renderRect{ x, y, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &renderRect); //renders the texture
}