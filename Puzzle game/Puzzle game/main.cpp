#include "raylib.h"
#include "player.h"
#include "Player_Camera.h"
#include "Puzzle.h"
#include <iostream>


//========0722=========
//struct Map1
//{
//    float MapX, MapY;
//    float MapWidth, MapHeight;
//    Color MapColor;
//};
//=======================

//화면 상태 상수(겜시작/플레이)
const int SCREEN_TITLE = 0;
const int SCREEN_GAMEPLAY = 1;
const int SCREEN_MENU = 2;

// 어쩌구저쩌구
int main(void)
{
   
    //시작화면 변수
    int screenState = SCREEN_TITLE;
    Rectangle Gstart = { 0, 0, 400, 100 };


    // 대충 화면
    InitWindow(800, 450, "Carry The Light");
    SetExitKey(KEY_NULL);

  
    // 헤더파일 구조체? 가져오기
    Player player;
    Player_Camera camera;
    Puzzle puz;


    // 게임 bgm
    InitAudioDevice();


    // 현재 창이 열려있는 모니터의 실제 해상도 (반드시 InitWindow 이후에 호출해야 함)
    // GetMonitorWidth(0)처럼 모니터 번호를 0으로 고정하면 멀티 모니터 환경에서
    // 게임 창이 다른 모니터에 있을 때 엉뚱한 해상도를 가져오는 문제가 있어서
    // GetCurrentMonitor()로 지금 창이 실제로 있는 모니터를 구함.
    // 이 값은 UI 배치/카메라 화면 크기 계산에만 쓰고, 맵 크기 계산에는 쓰지 않음!
    const int currentMonitor = GetCurrentMonitor();
    const float screenWidth = (float)GetMonitorWidth(currentMonitor);
    const float screenHeight = (float)GetMonitorHeight(currentMonitor);

    // 월드(맵) 좌표 - 모니터 해상도와 무관하게 고정 (Puzzle.h의 WORLD_X, WORLD_Y)
    // player.cpp와 값을 공유하기 때문에 모니터가 달라져도 맵/스폰 위치가 어긋나지 않음





    // 임시배경 **************** 바꿀 것
    Texture2D bgTexture = LoadTexture("Resource/back.jpg");

    // 임시 bgm
    Music bgm1 = LoadMusicStream("Resource/test_bgm1.ogg");
    Music bgm2 = LoadMusicStream("Resource/bgm2.ogg");



    /*

    // 임시 장애물 위치
    const WALL puzzles[] = {
        //==========0802=============
        {-WorldX, -WorldY, 200.0, WorldY*2, BLACK}, // 왼쪽 벽
        {WorldX, -WorldY, 200.0, WorldY * 2, BLACK}, // 오른쪽 벽

        {-WorldX, 700, WorldX*2, 200.0, BLACK}, // 아래 벽
        //===========================

        //==========0722=============
        // 왜인지 모르겠으나 기존에 있던 바닥3만 보이오.
        //
        //
        //{0, WorldY - 50, WorldX, 50.0f, BLACK} // 바닥1
        //{0, WorldY - screenHeight / 5, WorldX, 50.0f, BLACK}, // 바닥2
        {0, WorldY - 2 * screenHeight / 3, WorldX, 50.0f, BLACK}, // 바닥3
        //{WorldX - 50, WorldY - screenHeight / 3, 250.0f, screenHeight / 3 + 10 , BLACK}, // 바닥1 오른쪽 벽
        //{WorldX - 350, WorldY - 50 - player.width * 2 / 3,  300.0f, player.width * 2 / 3 + 10, BLACK}, // 바닥1 오른쪽 단차(?)
        //{WorldX / 2, WorldY - player.width * 4, 200.0f, player.width * 4 + 10 , BLACK},
        //{WorldX / 2 - 100, WorldY - player.width * 3, 400.0f, player.width * 3 + 10 , BLACK},
        //{WorldX / 2 - 200, WorldY - player.width * 2, 600.0f, player.width * 2 + 10 , BLACK},
        ////===========================


        //{ 800.0, WorldY * 0.8 - 100, 100.0, 100.0,GRAY },
        //{ 1500.0, WorldY * 0.8 - 100, 100.0, 100.0, GRAY },
        //{ 2600.0, WorldY * 0.8 - 150, 150.0, 150.0 ,GRAY},
    };




    // 장애물 개수
    const int puzzleCount = 4;
    // 초록색 임시 장애물
    const float groundY = WorldY - 600;


    */

    // 대충 화면22
    SetWindowSize((int)screenWidth, (int)screenHeight);
    ToggleFullscreen(); // 전체화면


    PlayMusicStream(bgm1);
    SetMusicVolume(bgm1, 1.0f);

    PlayMusicStream(bgm2);
    SetMusicVolume(bgm2, 0.3f);


    // 타이머 설정
    SetTargetFPS(60); // 게임 루프 초당 60프레임이라는 뜻, 숫자가 클수록 게임에서 움직이는 것들이 빨리 움직임

    //버튼 위치
    Gstart = { screenWidth / 2 -200, screenHeight / 2 -50, 400, 100 };


    // 메뉴 변수
    bool shouldExit = false;
    int prevScreenState = SCREEN_GAMEPLAY; //메뉴 전 상태(게임중)기억
    Rectangle btnSettings = { screenWidth / 2 - 200, screenHeight / 2 - 80, 400, 80 };
    Rectangle btnExit = { screenWidth / 2 - 200, screenHeight / 2 + 20, 400, 80 };

    // Render, Update, Draw 여기서 함
    while (!WindowShouldClose() && !shouldExit)
    {
        float deltaTime = GetFrameTime();


        const WALL* wallArr;
        int outCount;


        //시작화면 클릭
        Vector2 mousePoint = GetMousePosition();
        bool buttonHovered = CheckCollisionPointRec(mousePoint, Gstart);

        //esc로 메뉴 열기/닫기
        if (IsKeyPressed(KEY_ESCAPE))
        {
            if (screenState == SCREEN_GAMEPLAY)
            {
                prevScreenState = screenState;
                screenState = SCREEN_MENU;
            }
            else if (screenState == SCREEN_MENU)
            {
                screenState = prevScreenState; //게임으로 복귀
            }
        }


        if (screenState == SCREEN_TITLE)
        {
            // UpdateMusicStream(bgm1);
            if (buttonHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
        
                screenState = SCREEN_GAMEPLAY;
            }
        }

        if (screenState == SCREEN_GAMEPLAY)
        {
            // UpdateMusicStream(bgm2);

            puz.Create_Wall(WORLD_X, WORLD_Y, wallArr, outCount);

            player.Update(deltaTime, wallArr, outCount);

            //리셋
            if (IsKeyPressed(KEY_R))
            {
                player.Reset();
            }
        }

        else if (screenState == SCREEN_MENU)
        {
            bool exitHovered = CheckCollisionPointRec(mousePoint, btnExit);
            bool settingsHovered = CheckCollisionPointRec(mousePoint, btnSettings);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (exitHovered)
                {
                    shouldExit = true; //게임 종료
                }
                else if (settingsHovered)
                {
                    //설정버튼내용들 왈르르르ㅡㄹ
                }
            }
        }



        // ***** 플레이어 x, y축 좌표, 얘네가 받음
        float playerX = player.GetX();
        float playerY = player.GetY();
        // *****





        // 카메라 업데이트
        if (screenState == SCREEN_GAMEPLAY)
        {
            camera.Update(screenWidth, screenHeight, playerX, playerY); // 휠로 줌인아웃 가능(근데 지금 좀 이상함), 카메라가 플레이어 따라다님
        }


        // Draw
        BeginDrawing();



        ClearBackground(RAYWHITE);


        if (screenState == SCREEN_GAMEPLAY)
        {
            BeginMode2D(camera.GetCamera());




            // 카메라 상관없이 고정인 것들 + 장애물이랑 퍼즐들 여기 아래에 추가 하면 됨





            // 배경 draw **************** 바꿀 것
            Rectangle source = { 0, 0, (float)bgTexture.width, (float)bgTexture.height }; // 원본 이미지 전체
            Rectangle dest = { -WORLD_X, -WORLD_Y * 0.6f, WORLD_X * 2.0f, WORLD_Y };  // 그릴 목표 크기 (월드 크기에 맞춤)
            Vector2 origin = { 0, 0 };

            DrawTexturePro(bgTexture, source, dest, origin, 0.0f, WHITE);



            puz.Draw_Wall();
            

            /*
            
            // 장애물들
            for (int i = 0; i < puzzleCount; i++)
            {
                DrawRectangle(
                    (int)puzzles[i].x,
                    (int)puzzles[i].y,
                    (int)puzzles[i].width,
                    (int)puzzles[i].height,

                    puzzles[i].color // 장애물 색깔
                );
            }

            */

            player.Render();

            EndMode2D();EndMode2D();

        }
        else if (screenState == SCREEN_TITLE)
        {
            //시작화면
            Color buttonColor = buttonHovered ? DARKGRAY : GRAY;
            DrawRectangleRec(Gstart, buttonColor);
            DrawRectangleLinesEx(Gstart, 2, BLACK);

            const char* btnText = "GAME START";
            int textWidth = MeasureText(btnText, 20);
            DrawText(btnText,
                (int)(Gstart.x + Gstart.width / 2 - textWidth / 2),
                (int)(Gstart.y + Gstart.height / 2 - 10),
                20, WHITE);
        }

        //메뉴화면
        else if (screenState == SCREEN_MENU)
        {
            //배경
            DrawRectangle(0, 0, (int)screenWidth, (int)screenHeight, BLACK);

            bool exitHovered = CheckCollisionPointRec(mousePoint, btnExit);
            bool settingsHovered = CheckCollisionPointRec(mousePoint, btnSettings);

            //설정
            DrawRectangleRec(btnSettings, settingsHovered ? DARKGRAY : GRAY);
            DrawRectangleLinesEx(btnSettings, 2, BLACK);
            const char* settingsText = "SETTING";
            int settingsTextWidth = MeasureText(settingsText, 20);
            DrawText(settingsText,
                (int)(btnSettings.x + btnSettings.width / 2 - settingsTextWidth / 2),
                (int)(btnSettings.y + btnSettings.height / 2 - 10),
                20, WHITE);

            //게임 종료
            DrawRectangleRec(btnExit, exitHovered ? DARKGRAY : GRAY);
            DrawRectangleLinesEx(btnExit, 2, BLACK);
            const char* exitText = "EXIT";
            int exitTextWidth = MeasureText(exitText, 20);
            DrawText(exitText,
                (int)(btnExit.x + btnExit.width / 2 - exitTextWidth / 2),
                (int)(btnExit.y + btnExit.height / 2 - 10),
                20, WHITE);

        }


        // 초기화
    
        EndDrawing();

        // 임시배경

    }

    UnloadMusicStream(bgm1);
    UnloadMusicStream(bgm2);
    CloseAudioDevice();


    UnloadTexture(bgTexture);
    CloseWindow();
    

    return 0;
}