#include "player.h"
#include "math.h"

// 가짜 전역변수들(절대 바뀌지 않는 것들 ex.컴퓨터화면 크기)
//const float screenWidth = GetMonitorWidth(0);
//const float screenHeight = GetMonitorHeight(0);

// 월드 좌표
const float WorldX = 1700.0f;    // 맵 전체 가로 길이
const float WorldY = 1300.0f;     // 월드 기준 바닥의 y좌표 (고정)

Player::Player()
{
	// -WorldX + 1100, -WorldY + 1300
	position = { 100, -1000 };

	speed = 500.0f;

	width = 100.0f;
	height = 120.0f;

	velocityY = 0;

	isGrounded = false;

	//이미지(투명이 아니라 수정해야 할듯 ㅎ)
	idle = LoadTexture(R"(C:\puzzle\Puzzle-game\Puzzle game\Puzzle game\Resource\player_idle.png)");

	move = LoadTexture(R"(C:\puzzle\Puzzle-game\Puzzle game\Puzzle game\Resource\player_move.png)");


	//프레임
	idleFramecnt = 4;
	moveFramecnt = 3;

	curFrame = 0;

	frameTimer = 0.0f;

	// 프레임당 시간
	frameDuration = 0.12f;

	isMove = false;
	facingLeft = false;
}

void Player::Update(float deltaTime, const WALL puzzles[], int puzzleCount)
{
	float next_X = position.x; // 수평 충돌 확인을 위한 변수

	// 양 옆 이동
	if (IsKeyDown(KEY_D)) {
		next_X += speed * deltaTime;
		facingLeft = false;
	}

	if (IsKeyDown(KEY_A)) {
		next_X -= speed * deltaTime;
		facingLeft = true;
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

	isMove = !block_X && (IsKeyDown(KEY_A) || IsKeyDown(KEY_D));

	UpdateAnimation(deltaTime);

	
}
float Player::GetX() {
	return position.x;
}

float Player::GetY() {
	return position.y;
}

void Player::UpdateAnimation(float deltaTime)
{
	frameTimer += deltaTime;

	if (frameTimer >= frameDuration) {
		frameTimer = 0.0f;
		curFrame++;

		if (isMove) {
			if (curFrame >= moveFramecnt) {
				curFrame = 0;
			}
		}

		else {
			if (curFrame >= idleFramecnt) {
				curFrame = 0;
			}
		}
	}
}

void Player::Render()
{
	Texture2D texture;

	int frameCnt;

	if (isMove) {
		texture = move;
		frameCnt = moveFramecnt;
	}
	else {
		texture = idle;
		frameCnt = idleFramecnt;
	}

	float_t frameWidth = (float)texture.width / frameCnt;

	Rectangle source = {
		curFrame * frameWidth, 0, frameWidth, (float)texture.height };

	// 왼쪽바라볼때 좌우반전
	if (facingLeft) {
		source.x += frameWidth;
		source.width = -frameWidth;
	}

	// 출력될 위치/크기

	Rectangle destination = {
		position.x,
		position.y,
		width,
		height };

	DrawTexturePro(
		texture,
		source,
		destination,
		{ 0, 0 },
		0.0f,
		WHITE
	);
}

Player::~Player()
{
	UnloadTexture(idle);
	UnloadTexture(move);
}


