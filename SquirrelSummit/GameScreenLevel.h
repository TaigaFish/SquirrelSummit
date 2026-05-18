#pragma once
#ifndef _GAMESCREENLEVEL_H
#define _GAMESCREENLEVEL_H

#include "GameScreen.h"
#include "Texture2D.h"
#include "Character.h"
#include "LoadingZone.h"
#include <string>

class GameScreenLevel : public GameScreen
{
public:
	GameScreenLevel(SDL_Renderer* renderer, std::string backgroundPath);
	virtual ~GameScreenLevel();
protected:
	Texture2D* m_background_texture;
	Character* my_character;
	LoadingZone* loading_zone;

	void Render() override;
private:
	bool SetUpLevel(std::string backgroundPath);
};

#endif // !_GAMESCREENLEVEL_H