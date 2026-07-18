#include "player.h"
#include "math.h"

Player::Player()
{
	position = { 100.0f, 300.0f };

	speed = 250.0f;

	width = 50.0f;
	height = 50.0f;

	velocityY = 0;

	isGrounded = false;

}

void Player::Update(float deltaTime, const PUZZLE puzzles[], int puzzleCount)
{
	float next_X = position.x; // 수평 충돌 확인을 위한 변수

	// 양 옆 이동
	if (IsKeyDown(KEY_D)) {
		next_X += speed * deltaTime;
	}

	if (IsKeyDown(KEY_A)) {
		next_X -= speed * deltaTime;
	}

	Rectangle NearObs = { next_X, position.y, width, height }; // 근처 장애물


	bool block_X = false;
	for (int i = 0; i < puzzleCount; ++i) {
		Rectangle RectObs = { puzzles[i].x, puzzles[i].y, puzzles[i].width, puzzles[i].height };
		if (CheckCollisionRecs(NearObs, RectObs)) {
			block_X = true;

			break;
		}
	}

	if (!block_X) {
		position.x = next_X;
	}





	// 중력
	velocityY += 1000.0f * deltaTime;
	float next_Y = position.y + velocityY * deltaTime;

	// ---- 천장 체크 (위로 이동 중일 때만) ----
	if (velocityY < 0) {
		for (int i = 0; i < puzzleCount; ++i) {
			(position.x < puzzles[i].x + puzzles[i].width)
				&& (position.x + width > puzzles[i].x);

			float ceiling_Y = puzzles[i].y + puzzles[i].height;

			if ((position.x < puzzles[i].x + puzzles[i].width) && (position.x + width > puzzles[i].x)
				&& (position.y >= ceiling_Y)
				&& (next_Y <= ceiling_Y))
			{
				next_Y = ceiling_Y;   // 천장 바로 아래에서 딱 멈춤
				velocityY = 0.0f; // 속도 즉시 0 (쿵!)
				break;
			}
		}
	}


	// 바닥 체크
	bool find_ground = false;
	float groundY = 0.0;

	for (int i = 0; i < puzzleCount; ++i) {


		if ((position.x < puzzles[i].x + puzzles[i].width) && (position.x + width > puzzles[i].x) // 장애물 가로 끝에 닿인다면
			&& (position.y + height <= puzzles[i].y) // 장애물이 위에 있다면
			&& (next_Y + height >= puzzles[i].y))  // 장애물이 아래에 있다면
		{
			find_ground = true;
			groundY = puzzles[i].y - height;
			break;
		}
	}
	if (find_ground) {
		position.y = groundY;
		velocityY = 0;
		isGrounded = true;
	}
	else {
		position.y = next_Y;
		isGrounded = false;
	}






	// 점프
	if (IsKeyPressed(KEY_SPACE) && isGrounded) {
		velocityY = -500.0f;
		isGrounded = false;
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
