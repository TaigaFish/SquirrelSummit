#pragma once
#ifndef _GAMETEXT_H
#define _GAMETEXT_H
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class GameText
{
public:
	GameText(SDL_Renderer* renderer, const std::string& fontPath, unsigned int fontSize);
	~GameText();

	bool LoadFont(const std::string& fontPath, unsigned int fontSize);

	void RenderAt(const std::string& text, int x, int y);
	void RenderCentered(const std::string& text, int x, int y);
	void SetColor(SDL_Color color);
protected:
	SDL_Texture* texture;
	TTF_Font* font;
	SDL_Color color { 255, 255, 255, 255 };
	SDL_Renderer* renderer;
private:
	void Destroy();

	static bool ttfHasInit;
	static bool InitTTF();

	bool errorEncountered = false;

	void SetupRender(const std::string& text, int& w, int& h);
	void Render(int x, int y, int w, int h);
};

#endif // !_GAMETEXT_H