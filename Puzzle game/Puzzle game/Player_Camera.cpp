#include "Player_Camera.h"
#include "raylib.h"
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
    camera.offset = { screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;

    // 휠로 줌인아웃
    camera.zoom = expf(logf(camera.zoom) + (GetMouseWheelMove() * 0.1f));


    // 최대확대
    if (camera.zoom > 2.3f) {
        camera.zoom = 2.3f;
    }

    // 최소축소
    if (camera.zoom < 1.0f) {
        camera.zoom = 1.0f;
    }

    // 카메라 제한 -> 월드좌표 바깥으로 카메라 안넘어가게끔 >> 하고싶었는데 수정필요함~
    if (camera.target.y + screenHeight/camera.zoom/2 >= 800.0f)
        camera.target.y = 800.0f - screenHeight/ camera.zoom / 2;
    //if (camera.target.x + screenWidth / camera.zoom / 2  >= 3000.0f)
    //    camera.target.x = 3000.0f - screenWidth / camera.zoom / 2;
    //if (camera.target.x - screenWidth / camera.zoom / 2 <= 0.0f)
    //    camera.target.x = screenWidth / camera.zoom / 2;
}




Camera2D Player_Camera::GetCamera() const
{
    return camera;
}
