#include "Puzzle.h"
#define wallcount 3     // ******* 장애물 추가시 count 직접 늘려주기!!! *******
#define puzzlecount 3   // ******* 장애물 추가시 count 직접 늘려주기!!! *******


static WALL wall[wallcount];
static PUZZLE puzzle[puzzlecount];


Puzzle::Puzzle() 
{

}

void Puzzle::Create_Wall(float WorldX, float WorldY, const WALL*& wallArr, int& outCount)
{
    // ******* 장애물 추가하는 곳 *******
    wall[0] = { -WorldX, -WorldY, 200.0f, WorldY * 2, BLACK };  // 왼쪽 세로 벽
    wall[1] = { WorldX, -WorldY, 200.0f, WorldY * 2, BLACK };   // 오른쪽 세로 벽
    wall[2] = { -WorldX, 700, WorldX * 2, 200.0f, BLACK };      // 아래 바닥


    wallArr = wall;
    outCount = wallcount;
}


void Puzzle::Create_Puzzle(float WorldX, float WorldY, const PUZZLE*& puzzleArr, int& outCount)
{
    // ******* 장애물 추가하는 곳 *******
    // [예시]
    puzzle[0] = { -WorldX, -WorldY, 200.0f, WorldY * 2, BLACK };
    

    puzzleArr = puzzle;
    outCount = wallcount;
}


void Puzzle::Draw_Wall()
{

    for (int i = 0; i < wallcount; i++)
    {
        DrawRectangle(
            (int)wall[i].x,
            (int)wall[i].y,
            (int)wall[i].width,
            (int)wall[i].height,

            wall[i].color // 장애물 색깔

        );
    }
}