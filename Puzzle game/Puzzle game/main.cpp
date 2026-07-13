#include "raylib.h"
#include "player.h"
#include "Player_Camera.h"
#include "Puzzle.h"

int main(void)
{
 
    // 대충 화면
    InitWindow(800, 450, "Carry The Light"); 

    // 가짜 전역변수들(절대 바뀌지 않는 것들 ex.컴퓨터화면 크기)
    const float screenWidth = GetMonitorWidth(0);
    const float screenHeight = GetMonitorHeight(0);

    // 월드 좌표
    const float WorldX = 3000.0f;    // 맵 전체 가로 길이
    const float WorldY = 800.0f;     // 월드 기준 바닥의 y좌표 (고정)
    
   
    // 임시 장애물 위치
    const PUZZLE puzzles[] = {
    { 800,  700, 100, 100 },
    { 1500, 700, 100, 100 },
    { 2600, 650, 150, 150 },
    };

    
    // 임시 장애물 ;;
    const int obstacleCount = 3;
    // 초록색 임시 장애물
    const float groundY = screenHeight - 200; 



    // 대충 화면22
    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen(); // 전체화면


    // 타이머 설정
    SetTargetFPS(60); // 게임 루프 초당 60프레임이라는 뜻, 숫자가 클수록 우리 게임에서 움직이는 것들이 빨리 움직임




    // 헤더파일 구조체? 가져오기
    Player player;
    Player_Camera camera;


    // Render, Update, Draw 여기서 함
    while (!WindowShouldClose())    
    {
        float deltaTime = GetFrameTime();

        player.Update(deltaTime);





        // ***** 플레이어 x, y축 좌표, 얘네가 받음
        float playerX = player.GetX();
        float playerY = player.GetY();
        // *****





        // 카메라 업데이트
        camera.Update(screenWidth, screenHeight, playerX, playerY); // 휠로 줌인아웃 가능(근데 지금 좀 이상함), 카메라가 플레이어 따라다님


        // Draw
        BeginDrawing();



        ClearBackground(RAYWHITE);



        BeginMode2D(camera.GetCamera());



        // 카메라 상관없이 고정인 것들 + 장애물이랑 퍼즐들 여기 아래에 추가 하면 됨

        // 바닥
        DrawRectangle(0, groundY, screenWidth, screenHeight - groundY, DARKGREEN);

        // 7.14 하영
        // 바닥 (월드 좌표 기준, 화면 크기와 무관하게 고정)
        DrawRectangle(0, WorldY, WorldX, 300, DARKGREEN);

        // 장애물들
        for (int i = 0; i < obstacleCount; i++)
        {
            DrawRectangle(
                (int)puzzles[i].x,
                (int)puzzles[i].y,
                (int)puzzles[i].width,
                (int)puzzles[i].height,
                GRAY
            );
        }

        player.Render();
        
        
        

        // 초기화
        EndMode2D();
        EndDrawing();
       
    }


    CloseWindow();   

    return 0;
}
