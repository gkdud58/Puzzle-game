#pragma once
#include "raylib.h"

// 월드(맵) 크기 - 모니터 해상도와 무관하게 항상 고정된 값!!
// (예전엔 screenHeight 기준으로 계산해서 모니터마다 맵 크기/스폰 위치가 달라지는 버그가 있었음)
// main.cpp, player.cpp, Puzzle.cpp 전부 이 값 하나만 씀 -> 좌표계가 안 어긋남
// 맵 크기를 바꾸고 싶으면 여기 값만 수정하면 됨
constexpr float WORLD_X = 1700.0f;   // 맵 전체 가로 절반 길이
constexpr float WORLD_Y = 1400.0f;   // 맵 전체 세로 절반 길이

enum SHAPE
{
    RECT,
    TRI,
    CIR
};

struct WALL
{
    float x;
    float y;
    float width;
    float height;
    Color color;
    SHAPE shape;
};

struct PUZZLE
{
    float x;
    float y;
    float width;
    float height;
    Color color;
};

struct SEESAW // 중력받는 물체 구조체
{
    float x;
    float y;
    float rad;
};



class Puzzle
{
private :


public: 
    Puzzle();

    void Create_Wall(float WorldX, float WorldY, const WALL*& puzzleArr, int& outCount);

    void Create_Puzzle(float WorldX, float WorldY, const PUZZLE*& puzzleArr, int& outCount);

    void Create_SeeSaw(float WorldX, float WorldY);

    void Draw_Wall();
};

