#include "Player_Camera.h"
#include "raylib.h"
#include "math.h"

Player_Camera::Player_Camera()
{
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom;
}


void Player_Camera::Update(float screenWidth, float screenHeight, float playerX, float playerY)
{
    camera.target = { playerX + 20, playerY + 20};
    camera.offset = { screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom;

    // 휠로 줌인아웃
    camera.zoom = expf(logf(camera.zoom) + (GetMouseWheelMove() * 0.1f));


    // 최대확대
    if (camera.zoom > 3.0f) {
        camera.zoom = 3.0f;
    }

    // 최소축소
    if (camera.zoom < 1.0f) {
        camera.zoom = 1.0f;
    }

    // 카메라 제한 -> 월드좌표 바깥으로 카메라 안넘어가게끔 >> 하고싶었는데 수정필요함~
    if (camera.target.y + screenHeight/2 >= 800.0f)
        camera.target.y = 900.0f - screenHeight/2; 
    if (camera.target.x >= 3000.0f)
        camera.target.x = 3000.0f;
    if (camera.target.x <= 0.0f)
        camera.target.x = 0.0f;
}




Camera2D Player_Camera::GetCamera() const
{
    return camera;
}
