#pragma once
#include "raylib.h"


struct WALL
{
    float x;
    float y;
    float width;
    float height;
    Color color;
};

struct PUZZLE
{
    float x;
    float y;
    float width;
    float height;
    Color color;
};

class Puzzle
{
private :
    float x;
    float y;
    float width;
    float height;


public: 
    Puzzle();

    void Create_Wall(float WorldX, float WorldY, const WALL*& puzzleArr, int& outCount);

    void Create_Puzzle(float WorldX, float WorldY, const PUZZLE*& puzzleArr, int& outCount);

    void Draw_Wall();
};

