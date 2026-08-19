#pragma once
#include "raylib.h"

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

