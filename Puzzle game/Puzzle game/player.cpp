#include "player.h"

Player::Player()
{
	position = { 100.0f, 300.0f };

	speed = 250.0f;

	width = 50.0f;
	height = 50.0f;

	velocityY = 0;

	isGrounded = false;

}

void Player::Update(float deltaTime) 
{

	// 양 옆 이동
	if (IsKeyDown(KEY_D)) {
		position.x += speed * deltaTime;
	}

	if (IsKeyDown(KEY_A)) {
		position.x -= speed * deltaTime;
	}

	velocityY += 1000.0f * deltaTime;
	position.y += velocityY * deltaTime;

	// 바닥 충돌
	float groundY = GetMonitorHeight(0) - 200;

	// 바닥에 닿았을 때
	if (position.y + height >= groundY) {
		
		position.y = groundY - height;
		velocityY = 0.0f;
		isGrounded = true;
	}
	else {
		isGrounded = false;
	}


	// 점프
	if (IsKeyPressed(KEY_SPACE) && isGrounded) {
		velocityY = -500.0f;
		isGrounded = false;
	}

	// 화면 밖으로 안나가게
	if (position.x < 0) {
		position.x = 0;
	}

	if (position.x + width > GetScreenWidth()) {
		position.x = GetScreenWidth() - width;
	}
}

float Player::GetX() {
	return position.x;
}

float Player::GetY() {
	return position.y;
}

void Player::Render()
{
	DrawRectangle(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(width),
		static_cast<int>(height),
		BLUE
	);

}
