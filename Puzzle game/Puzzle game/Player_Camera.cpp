#include "Player_Camera.h"
#include "raylib.h"
#include "Puzzle.h"   // WORLD_X, WORLD_Y (모니터 해상도와 무관한 고정 맵 크기)
#include "math.h"

Player_Camera::Player_Camera()
{
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom=1.0f;
}
void Player_Camera::Update(float screenWidth, float screenHeight, float playerX, float playerY)
{
    camera.target = { playerX + 20, playerY + 20};
    camera.offset = { screenWidth / 2 , screenHeight / 2 /* + 250 */};
    camera.rotation = 0.0f;

    // 휠로 줌인아웃
    camera.zoom = expf(logf(camera.zoom) + (GetMouseWheelMove() * 0.1f));


    // 최대확대
    if (camera.zoom > 2.3f) {
        camera.zoom = 2.3f;
    }

    // 최소축소
    // 모니터가 커서 화면(screenWidth/screenHeight)이 맵(WORLD_X*2, WORLD_Y*2)보다 넓어지면
    // zoom을 1.0까지 줄여도 맵 바깥 빈 공간이 보이거나 맵 전체가 한 번에 다 보여버림.
    // 그래서 "화면 크기 / 맵 크기"보다 작게는 줄어들지 않도록 최소 줌을 화면 크기에 맞춰 계산함.
    float minZoomX = screenWidth / (2.0f * WORLD_X);
    float minZoomY = screenHeight / (2.0f * WORLD_Y);
    float minZoom = 1.0f;
    if (minZoomX > minZoom) minZoom = minZoomX;
    if (minZoomY > minZoom) minZoom = minZoomY;

    if (camera.zoom < minZoom) {
        camera.zoom = minZoom;
    }

    // 카메라 제한 -> 월드좌표 바깥으로 카메라 안넘어가게끔
    // (예전엔 800.0f / 3000.0f 같은 값이 하드코딩+주석처리 되어 있었는데,
    //  실제 맵 경계인 WORLD_X/WORLD_Y 기준으로 다시 계산해서 켜둠)
    float halfViewW = screenWidth / camera.zoom / 2.0f;
    float halfViewH = screenHeight / camera.zoom / 2.0f;

    float minX = -WORLD_X + halfViewW;
    float maxX = WORLD_X - halfViewW;
    if (minX > maxX) {
        camera.target.x = 0.0f; // 화면이 맵보다 넓으면 가운데 고정
    } else {
        if (camera.target.x < minX) camera.target.x = minX;
        if (camera.target.x > maxX) camera.target.x = maxX;
    }

    float minY = -WORLD_Y + halfViewH;
    float maxY = WORLD_Y - halfViewH;
    if (minY > maxY) {
        camera.target.y = 0.0f;
    } else {
        if (camera.target.y < minY) camera.target.y = minY;
        if (camera.target.y > maxY) camera.target.y = maxY;
    }
}




Camera2D Player_Camera::GetCamera() const
{
    return camera;
}
