#pragma once

#include "raylib.h"

class Player
{
private:

	// 위치
	Vector2 position;

	// 속도
	float speed;
	
	// 크기
	float width;
	float height;

	bool isGrounded;


	// 상하 속도(중력)
	float velocityY;

public:

	Player();

	// 키 입력 & 이동 처리
	void Update(float deltaTime);
	
	float GetX();
	float GetY();

	// 출력
	void Render();


};