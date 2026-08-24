#include "player.h"
#include "math.h"

// 주의: 예전엔 여기서 GetMonitorWidth(0)/GetMonitorHeight(0)을 전역변수로 호출했었는데,
// 이 코드는 InitWindow()보다 먼저(프로그램 시작 시점에) 실행돼서 항상 0을 반환하는 버그가 있었음.
// 게다가 맵 크기(WorldX, WorldY)를 여기서 따로 만들어서 main.cpp가 만드는 맵 좌표계랑 어긋났음.
// -> WORLD_X, WORLD_Y는 이제 Puzzle.h에 고정값으로 정의해서 모든 파일이 공유함.

Player::Player()
{
	speed = 500.0f;

	width = 80.0f;
	height = 100.0f;

	// 시작 발판(Puzzle.cpp의 wall[7], x=-WORLD_X+1100, y=-WORLD_Y+1300) 위에 스폰
	position = { -WORLD_X + 1100, -WORLD_Y + 1300 - height };

	velocityY = 0;

	isGrounded = false;

	//이미지(투명이 아니라 수정해야 할듯)
	idle = LoadTexture(R"(Resource\player_idle.png)");

	move = LoadTexture(R"(Resource\player_move.png)");


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



void Player::Reset()
{
	position = { -WORLD_X + 1100, -WORLD_Y + 1300 - height };
	velocityY = 0;
	isGrounded = false;
}
