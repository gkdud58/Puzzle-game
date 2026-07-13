#pragma once
#include "raylib.h"

class Player_Camera
{
private:
	Camera2D camera;

public:
	Player_Camera();

	void Update(float screenWidth, float screenHeight, float playerX, float playerY);

	Camera2D GetCamera() const;
};

