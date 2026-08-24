#pragma once

#include "raylib.h"
#include "Puzzle.h"

class Player
{
private:

	// 위치
	Vector2 position;

	// 속도
	float speed;
	
	
	bool isGrounded;


	// 상하 속도(중력)
	float velocityY;

	Texture2D idle;
	Texture2D move;

	int curFrame;
	int idleFramecnt;
	int moveFramecnt;

	float frameTimer;
	float frameDuration;

	bool isMove;
	bool facingLeft;

	void UpdateAnimation(float deltaTime);

public:

	Player();
	~Player();

	// 크기 // private -> public 이동 (main.cpp에서 사용하려고)
	float width;
	float height;


	// 키 입력 & 이동 처리
	void Update(float deltaTime, const WALL puzzles[], int puzzleCount);
	
	float GetX();
	float GetY();

	// 출력
	void Render();


};