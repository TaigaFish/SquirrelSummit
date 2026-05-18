#pragma once

struct Vector2D
{
	float x;
	float y;
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

enum SCREENS
{
	SCREEN_NONE,
	SCREEN_MENU,
	SCREEN_HELP_EVERCADE,
	SCREEN_HELP_WINDOWS,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_LEVEL3,
	SCREEN_END
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};

enum CollisionDir
{
	COLLISION_NONE,
	COLLISION_UP,
	COLLISION_DOWN,
	COLLISION_LEFT,
	COLLISION_RIGHT
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;
	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}
	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

struct Collision2D
{
	Rect2D boundaries;
	Vector2D offset; //how the top left of the collision is offset from the top left of the sprite
	Collision2D(Rect2D bounds, Vector2D offset)
	{
		boundaries = bounds;
		this->offset = offset;
	}
};

enum Input
{
	INPUT_NONE,
	INPUT_DOWN_UP,
	INPUT_DOWN_DOWN,
	INPUT_DOWN_LEFT,
	INPUT_DOWN_RIGHT,
	INPUT_DOWN_JUMP,
	INPUT_DOWN_DASH,
	INPUT_DOWN_THROW,
	INPUT_DOWN_FLOAT,
	INPUT_UP_UP,
	INPUT_UP_DOWN,
	INPUT_UP_LEFT,
	INPUT_UP_RIGHT,
	INPUT_UP_JUMP,
	INPUT_UP_DASH,
	INPUT_UP_THROW,
	INPUT_UP_FLOAT
};