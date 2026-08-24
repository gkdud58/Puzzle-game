#include "Puzzle.h"
#define wallcount 50    // ******* 장애물 추가시 count 직접 늘려주기!!! *******
#define puzzlecount 3   // ******* 장애물 추가시 count 직접 늘려주기!!! *******


static WALL wall[wallcount];
static PUZZLE puzzle[puzzlecount];
static SEESAW seesaw[1];

Puzzle::Puzzle() 
{

}

void Puzzle::Create_Wall(float WorldX, float WorldY, const WALL*& wallArr, int& outCount)
{
    // ******* 장애물 추가하는 곳 *******
    // wall[wallcount] = { x축, y축, 가로크기, 세로크기, 색깔, 모양(아무것도 안 적으면 사각형으로 생성)};

    // 전체 맵 벽
    wall[0] = { -WorldX, -WorldY, 200.0f, WorldY * 2, BLACK };                                   // 왼쪽 세로 벽
    wall[1] = { WorldX, -WorldY, 200.0f, WorldY * 2, BLACK };                                    // 오른쪽 세로 벽
    wall[2] = { -WorldX, -WorldY + 2750, 2 * WorldX - 2000.0f, 200.0f,BLACK };                   // 중간 바닥 1 
    wall[18] = { -WorldX + 2000, -WorldY + 2750, 2 * WorldX - 2000.0f, 200.0f, BLACK };          // 중간 바닥 2
    wall[19] = { -WorldX, WorldY - 200, WorldX * 2, 200.0f, BLACK };                             // 아래 바닥
    wall[3] = { -WorldX, -WorldY + 650, WorldX * 2, 200.0f, BLACK };                             // 위 천장



    // *** 위 장애물 배치 ***
    wall[4] = { -WorldX , -WorldY + 650, 500, 700, BLACK };
    wall[5] = { WorldX - 300, -WorldY + 650, 500, 700, BLACK };

    // 위 전체 발판
    wall[6] = { -WorldX, -WorldY + 1300, 500 + 400, 300.0f, BLACK };
    wall[7] = { -WorldX + 1100, -WorldY + 1300, 1000, 300.0f, BLACK };
    wall[8] = { -WorldX + 2400, -WorldY + 1300, WorldX * 2 - 2400, 300.0f, BLACK };

    float a = 100;
    // 위 크로스 파쿠르
    wall[9]  = { -WorldX + 1100 + 1000, -WorldY + 1300, a, 20.0f, BLACK };
    wall[10] = { -WorldX + 2400 - a, -WorldY + 1300 + 90, a, 20.0f, BLACK };
    wall[11] = { -WorldX + 1100 + 1000, -WorldY + 1300 + 90*2, a, 20.0f, BLACK };
    wall[12] = { -WorldX + 2400 - a, -WorldY + 1300 + 280, a, 20.0f, BLACK };
    wall[13] = { -WorldX + 1100 + 1000, -WorldY + 1300 + 90*4, a, 20.0f, BLACK };

    wall[14] = { -WorldX + 1800, -WorldY + 1300, 300, 500, BLACK };


    // 중앙 시소 부분 바닥
    wall[15] = { -WorldX + 1800, -WorldY + 1800, WorldX * 2 - 2350, 70.0f, BLACK };
    wall[16] = { -WorldX + 3000, -WorldY + 1900, WorldX * 2 - 3000, 70.0f, BLACK };



    // 시소
    float seesaw_height = 30;
    wall[17] = { -WorldX + 2400, -WorldY + 1800 - seesaw_height, seesaw_height, seesaw_height, GREEN, TRI };



    // 아래 장애물 배치
    // 표지판 
    wall[20] = { -WorldX + 1000, WorldY - 750, 100.0f, 600.0f, BLACK };     // 기둥
    // 홀수 - 오른쪽 / 짝수 - 왼쪽
    wall[21] = { -WorldX + 1100, WorldY - 500, 100.0f, 30.0f, BLACK };     // 지그재그1 
    wall[22] = { -WorldX + 900, WorldY - 550, 100.0f, 30.0f, BLACK };      // 지그재그2
    wall[23] = { -WorldX + 1100, WorldY - 600, 100.0f, 30.0f, BLACK };     // 지그재그3
    wall[24] = { -WorldX + 900, WorldY - 650, 100.0f, 30.0f, BLACK };      // 지그재그4
    wall[25] = { -WorldX + 1100, WorldY - 700, 100.0f, 30.0f, BLACK };     // 지그재그5 
    wall[26] = { -WorldX + 900, WorldY - 750, 100.0f, 30.0f, BLACK };      // 지그재그6


    // 가로등 1
    wall[27] = { -WorldX + 700, WorldY - 350, 30.0f, 200.0f, BLACK };     // 세로 기둥
    wall[28] = { -WorldX + 700, WorldY - 380, 100.0f, 30.0f, BLACK };     // 가로 기둥

    // 가로등 2
    wall[29] = { -WorldX + 1300, WorldY - 450, 30.0f, 400.0f, BLACK };     // 세로 기둥
    wall[30] = { -WorldX + 1280, WorldY - 450, 70.0f, 30.0f, BLACK };      // 가로 기둥

    // 가로등 3
    wall[31] = { -WorldX + 1600, WorldY - 450, 30.0f, 400.0f, BLACK };     // 세로 기둥
    wall[32] = { -WorldX + 1580, WorldY - 450, 70.0f, 30.0f, BLACK };      // 가로 기둥

    // 가로등 4
    wall[33] = { -WorldX + 1900, WorldY - 450, 30.0f, 400.0f, BLACK };     // 세로 기둥
    wall[34] = { -WorldX + 1880, WorldY - 450, 70.0f, 30.0f, BLACK };      // 가로 기둥

    // 가로등 5
    wall[35] = { -WorldX + 2200, WorldY - 450, 30.0f, 400.0f, BLACK };     // 세로 기둥
    wall[36] = { -WorldX + 2180, WorldY - 450, 70.0f, 30.0f, BLACK };      // 가로 기둥

    // 가로등 6
    wall[37] = { -WorldX + 2500, WorldY - 450, 30.0f, 400.0f, BLACK };     // 세로 기둥
    wall[38] = { -WorldX + 2480, WorldY - 450, 70.0f, 30.0f, BLACK };      // 가로 기둥

    wallArr = wall;
    outCount = wallcount;
}


void Puzzle::Create_Puzzle(float WorldX, float WorldY, const PUZZLE*& puzzleArr, int& outCount)
{
    // ******* 장애물 추가하는 곳 *******
    // [예시]
    puzzle[0] = { -WorldX, -WorldY, 200.0f, WorldY * 2, BLACK };


    puzzleArr = puzzle;
    outCount = puzzlecount;
}

void Puzzle::Create_SeeSaw(float WorldX, float WorldY) 
{

}

void Puzzle::Draw_Wall()
{
    
    for (int i = 0; i < wallcount; i++)
    {
        if (wall[i].shape == RECT)
        {
            DrawRectangle((int)wall[i].x, (int)wall[i].y, (int)wall[i].width, (int)wall[i].height, wall[i].color);
        }
        else if (wall[i].shape == TRI)
        {
            DrawTriangle({ wall[i].x, wall[i].y + wall[i].height }, { wall[i].x + wall[i].width, wall[i].y + wall[i].height }, { wall[i].x + wall[i].width / 2, wall[i].y }, wall[i].color);
        }
        else if (wall[i].shape == CIR)
        {
            float radius = wall[i].width / 2;
            DrawCircle((int)(wall[i].x + radius), (int)(wall[i].y + radius), radius, wall[i].color);
        }
        else
        {
            DrawRectangle((int)wall[i].x, (int)wall[i].y, (int)wall[i].width, (int)wall[i].height, wall[i].color);
        }
    }
}