
#include "raylib.h"
#include "player.h"

int main(void)
{
 
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Player player;

    while (!WindowShouldClose())    
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // 바닥
        DrawRectangle(0, 600, screenWidth, 120, DARKGREEN);
        
        player.Render();

        EndDrawing();
       
    }


    CloseWindow();   

    return 0;
}
